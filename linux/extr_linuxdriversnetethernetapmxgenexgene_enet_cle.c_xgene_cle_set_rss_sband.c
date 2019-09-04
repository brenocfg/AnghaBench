#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct xgene_enet_cle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLE_CMD_WR ; 
 int CLE_PKTRAM_SIZE ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  PKT_RAM ; 
 int /*<<< orphan*/  XGENE_CLE_IPV4 ; 
 int /*<<< orphan*/  XGENE_CLE_OTHER ; 
 int /*<<< orphan*/  XGENE_CLE_TCP ; 
 int /*<<< orphan*/  XGENE_CLE_UDP ; 
 int xgene_cle_dram_wr (struct xgene_enet_cle*,int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_cle_sband_to_hw (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int xgene_cle_set_rss_sband(struct xgene_enet_cle *cle)
{
	u32 idx = CLE_PKTRAM_SIZE / sizeof(u32);
	u32 mac_hdr_len = ETH_HLEN;
	u32 sband, reg = 0;
	u32 ipv4_ihl = 5;
	u32 hdr_len;
	int ret;

	/* Sideband: IPV4/TCP packets */
	hdr_len = (mac_hdr_len << 5) | ipv4_ihl;
	xgene_cle_sband_to_hw(0, XGENE_CLE_IPV4, XGENE_CLE_TCP, hdr_len, &reg);
	sband = reg;

	/* Sideband: IPv4/UDP packets */
	hdr_len = (mac_hdr_len << 5) | ipv4_ihl;
	xgene_cle_sband_to_hw(1, XGENE_CLE_IPV4, XGENE_CLE_UDP, hdr_len, &reg);
	sband |= (reg << 16);

	ret = xgene_cle_dram_wr(cle, &sband, 1, idx, PKT_RAM, CLE_CMD_WR);
	if (ret)
		return ret;

	/* Sideband: IPv4/RAW packets */
	hdr_len = (mac_hdr_len << 5) | ipv4_ihl;
	xgene_cle_sband_to_hw(0, XGENE_CLE_IPV4, XGENE_CLE_OTHER,
			      hdr_len, &reg);
	sband = reg;

	/* Sideband: Ethernet II/RAW packets */
	hdr_len = (mac_hdr_len << 5);
	xgene_cle_sband_to_hw(0, XGENE_CLE_IPV4, XGENE_CLE_OTHER,
			      hdr_len, &reg);
	sband |= (reg << 16);

	ret = xgene_cle_dram_wr(cle, &sband, 1, idx + 1, PKT_RAM, CLE_CMD_WR);
	if (ret)
		return ret;

	return 0;
}