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
struct TYPE_2__ {int is64b; int enb; } ;
union nps_pkt_in_instr_ctl {void* value; TYPE_1__ s; } ;
typedef  int /*<<< orphan*/  u64 ;
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPS_PKT_IN_INSTR_CTLX (int) ; 
 void* nitrox_read_csr (struct nitrox_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,void*) ; 

void enable_pkt_input_ring(struct nitrox_device *ndev, int ring)
{
	union nps_pkt_in_instr_ctl pkt_in_ctl;
	u64 offset;

	/* 64-byte instruction size */
	offset = NPS_PKT_IN_INSTR_CTLX(ring);
	pkt_in_ctl.value = nitrox_read_csr(ndev, offset);
	pkt_in_ctl.s.is64b = 1;
	pkt_in_ctl.s.enb = 1;
	nitrox_write_csr(ndev, offset, pkt_in_ctl.value);

	/* wait for set [ENB] */
	do {
		pkt_in_ctl.value = nitrox_read_csr(ndev, offset);
	} while (!pkt_in_ctl.s.enb);
}