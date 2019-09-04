#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ enb; } ;
union nps_pkt_slc_ctl {void* value; TYPE_1__ s; } ;
union nps_pkt_slc_cnts {void* value; } ;
typedef  int /*<<< orphan*/  u64 ;
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPS_PKT_SLC_CNTSX (int) ; 
 int /*<<< orphan*/  NPS_PKT_SLC_CTLX (int) ; 
 void* nitrox_read_csr (struct nitrox_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void reset_pkt_solicit_port(struct nitrox_device *ndev, int port)
{
	union nps_pkt_slc_ctl pkt_slc_ctl;
	union nps_pkt_slc_cnts pkt_slc_cnts;
	u64 offset;

	/* disable slc port */
	offset = NPS_PKT_SLC_CTLX(port);
	pkt_slc_ctl.value = nitrox_read_csr(ndev, offset);
	pkt_slc_ctl.s.enb = 0;
	nitrox_write_csr(ndev, offset, pkt_slc_ctl.value);
	usleep_range(100, 150);

	/* wait to clear [ENB] */
	do {
		pkt_slc_ctl.value = nitrox_read_csr(ndev, offset);
	} while (pkt_slc_ctl.s.enb);

	/* clear slc counters */
	offset = NPS_PKT_SLC_CNTSX(port);
	pkt_slc_cnts.value = nitrox_read_csr(ndev, offset);
	nitrox_write_csr(ndev, offset, pkt_slc_cnts.value);
	usleep_range(50, 100);
}