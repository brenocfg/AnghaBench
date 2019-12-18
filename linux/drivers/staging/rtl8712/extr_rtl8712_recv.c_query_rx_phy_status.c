#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int mcs_rate; int signal_qual; int* rx_mimo_signal_qual; int signal_strength; scalar_t__ htc; } ;
struct TYPE_8__ {TYPE_2__ attrib; scalar_t__ rx_head; } ;
struct TYPE_7__ {TYPE_4__ hdr; } ;
union recv_frame {TYPE_3__ u; } ;
typedef  int u8 ;
typedef  int u32 ;
struct recv_stat {int dummy; } ;
struct phy_stat {int /*<<< orphan*/  phydw1; } ;
struct phy_cck_rx_status {int cck_agc_rpt; int sq_rpt; } ;
struct TYPE_5__ {int rf_config; } ;
struct _adapter {TYPE_1__ registrypriv; } ;
typedef  int s8 ;

/* Variables and functions */
 int PHY_STAT_GAIN_TRSW_SHT ; 
 size_t PHY_STAT_PWDB_ALL_SHT ; 
 int PHY_STAT_RXEVM_SHT ; 
 int evm_db2percentage (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int query_rx_pwr_percentage (int) ; 
 scalar_t__ r8712_signal_scale_mapping (int) ; 

__attribute__((used)) static void query_rx_phy_status(struct _adapter *padapter,
				union recv_frame *prframe)
{
	u8 i, max_spatial_stream, evm;
	struct recv_stat *prxstat = (struct recv_stat *)prframe->u.hdr.rx_head;
	struct phy_stat *pphy_stat = (struct phy_stat *)(prxstat + 1);
	u8 *pphy_head = (u8 *)(prxstat + 1);
	s8 rx_pwr[4], rx_pwr_all;
	u8 pwdb_all;
	u32 rssi, total_rssi = 0;
	u8 bcck_rate = 0, rf_rx_num = 0, cck_highpwr = 0;
	struct phy_cck_rx_status *pcck_buf;
	u8 sq;

	/* Record it for next packet processing*/
	bcck_rate = (prframe->u.hdr.attrib.mcs_rate <= 3 ? 1 : 0);
	if (bcck_rate) {
		u8 report;

		/* CCK Driver info Structure is not the same as OFDM packet.*/
		pcck_buf = (struct phy_cck_rx_status *)pphy_stat;
		/* (1)Hardware does not provide RSSI for CCK
		 * (2)PWDB, Average PWDB calculated by hardware
		 * (for rate adaptive)
		 */
		if (!cck_highpwr) {
			report = pcck_buf->cck_agc_rpt & 0xc0;
			report >>= 6;
			switch (report) {
			/* Modify the RF RNA gain value to -40, -20,
			 * -2, 14 by Jenyu's suggestion
			 * Note: different RF with the different
			 * RNA gain.
			 */
			case 0x3:
				rx_pwr_all = -40 - (pcck_buf->cck_agc_rpt &
					     0x3e);
				break;
			case 0x2:
				rx_pwr_all = -20 - (pcck_buf->cck_agc_rpt &
					     0x3e);
				break;
			case 0x1:
				rx_pwr_all = -2 - (pcck_buf->cck_agc_rpt &
					     0x3e);
				break;
			case 0x0:
				rx_pwr_all = 14 - (pcck_buf->cck_agc_rpt &
					     0x3e);
				break;
			}
		} else {
			report = ((u8)(le32_to_cpu(pphy_stat->phydw1) >> 8)) &
				 0x60;
			report >>= 5;
			switch (report) {
			case 0x3:
				rx_pwr_all = -40 - ((pcck_buf->cck_agc_rpt &
					     0x1f) << 1);
				break;
			case 0x2:
				rx_pwr_all = -20 - ((pcck_buf->cck_agc_rpt &
					     0x1f) << 1);
				break;
			case 0x1:
				rx_pwr_all = -2 - ((pcck_buf->cck_agc_rpt &
					     0x1f) << 1);
				break;
			case 0x0:
				rx_pwr_all = 14 - ((pcck_buf->cck_agc_rpt &
					     0x1f) << 1);
				break;
			}
		}
		pwdb_all = query_rx_pwr_percentage(rx_pwr_all);
		/* CCK gain is smaller than OFDM/MCS gain,*/
		/* so we add gain diff by experiences, the val is 6 */
		pwdb_all += 6;
		if (pwdb_all > 100)
			pwdb_all = 100;
		/* modify the offset to make the same gain index with OFDM.*/
		if (pwdb_all > 34 && pwdb_all <= 42)
			pwdb_all -= 2;
		else if (pwdb_all > 26 && pwdb_all <= 34)
			pwdb_all -= 6;
		else if (pwdb_all > 14 && pwdb_all <= 26)
			pwdb_all -= 8;
		else if (pwdb_all > 4 && pwdb_all <= 14)
			pwdb_all -= 4;
		/*
		 * (3) Get Signal Quality (EVM)
		 */
		if (pwdb_all > 40) {
			sq = 100;
		} else {
			sq = pcck_buf->sq_rpt;
			if (pcck_buf->sq_rpt > 64)
				sq = 0;
			else if (pcck_buf->sq_rpt < 20)
				sq = 100;
			else
				sq = ((64 - sq) * 100) / 44;
		}
		prframe->u.hdr.attrib.signal_qual = sq;
		prframe->u.hdr.attrib.rx_mimo_signal_qual[0] = sq;
		prframe->u.hdr.attrib.rx_mimo_signal_qual[1] = -1;
	} else {
		/* (1)Get RSSI for HT rate */
		for (i = 0; i < ((padapter->registrypriv.rf_config) &
			    0x0f); i++) {
			rf_rx_num++;
			rx_pwr[i] = ((pphy_head[PHY_STAT_GAIN_TRSW_SHT + i]
				    & 0x3F) * 2) - 110;
			/* Translate DBM to percentage. */
			rssi = query_rx_pwr_percentage(rx_pwr[i]);
			total_rssi += rssi;
		}
		/* (2)PWDB, Average PWDB calculated by hardware (for
		 * rate adaptive)
		 */
		rx_pwr_all = (((pphy_head[PHY_STAT_PWDB_ALL_SHT]) >> 1) & 0x7f)
			     - 106;
		pwdb_all = query_rx_pwr_percentage(rx_pwr_all);

		{
			/* (3)EVM of HT rate */
			if (prframe->u.hdr.attrib.htc &&
			    prframe->u.hdr.attrib.mcs_rate >= 20 &&
			    prframe->u.hdr.attrib.mcs_rate <= 27) {
				/* both spatial stream make sense */
				max_spatial_stream = 2;
			} else {
				/* only spatial stream 1 makes sense */
				max_spatial_stream = 1;
			}
			for (i = 0; i < max_spatial_stream; i++) {
				evm = evm_db2percentage((pphy_head
				      [PHY_STAT_RXEVM_SHT + i]));/*dbm*/
				prframe->u.hdr.attrib.signal_qual =
					 (u8)(evm & 0xff);
				prframe->u.hdr.attrib.rx_mimo_signal_qual[i] =
					 (u8)(evm & 0xff);
			}
		}
	}
	/* UI BSS List signal strength(in percentage), make it good looking,
	 * from 0~100. It is assigned to the BSS List in
	 * GetValueFromBeaconOrProbeRsp().
	 */
	if (bcck_rate) {
		prframe->u.hdr.attrib.signal_strength =
			 (u8)r8712_signal_scale_mapping(pwdb_all);
	} else {
		if (rf_rx_num != 0)
			prframe->u.hdr.attrib.signal_strength =
				 (u8)(r8712_signal_scale_mapping(total_rssi /=
				 rf_rx_num));
	}
}