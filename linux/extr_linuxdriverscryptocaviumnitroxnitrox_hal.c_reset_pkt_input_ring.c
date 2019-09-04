#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ enb; } ;
union nps_pkt_in_instr_ctl {void* value; TYPE_1__ s; } ;
struct TYPE_4__ {int dbell; } ;
union nps_pkt_in_instr_baoff_dbell {void* value; TYPE_2__ s; } ;
union nps_pkt_in_done_cnts {void* value; } ;
typedef  int /*<<< orphan*/  u64 ;
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPS_PKT_IN_DONE_CNTSX (int) ; 
 int /*<<< orphan*/  NPS_PKT_IN_INSTR_BAOFF_DBELLX (int) ; 
 int /*<<< orphan*/  NPS_PKT_IN_INSTR_CTLX (int) ; 
 void* nitrox_read_csr (struct nitrox_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void reset_pkt_input_ring(struct nitrox_device *ndev, int ring)
{
	union nps_pkt_in_instr_ctl pkt_in_ctl;
	union nps_pkt_in_instr_baoff_dbell pkt_in_dbell;
	union nps_pkt_in_done_cnts pkt_in_cnts;
	u64 offset;

	offset = NPS_PKT_IN_INSTR_CTLX(ring);
	/* disable the ring */
	pkt_in_ctl.value = nitrox_read_csr(ndev, offset);
	pkt_in_ctl.s.enb = 0;
	nitrox_write_csr(ndev, offset, pkt_in_ctl.value);
	usleep_range(100, 150);

	/* wait to clear [ENB] */
	do {
		pkt_in_ctl.value = nitrox_read_csr(ndev, offset);
	} while (pkt_in_ctl.s.enb);

	/* clear off door bell counts */
	offset = NPS_PKT_IN_INSTR_BAOFF_DBELLX(ring);
	pkt_in_dbell.value = 0;
	pkt_in_dbell.s.dbell = 0xffffffff;
	nitrox_write_csr(ndev, offset, pkt_in_dbell.value);

	/* clear done counts */
	offset = NPS_PKT_IN_DONE_CNTSX(ring);
	pkt_in_cnts.value = nitrox_read_csr(ndev, offset);
	nitrox_write_csr(ndev, offset, pkt_in_cnts.value);
	usleep_range(50, 100);
}