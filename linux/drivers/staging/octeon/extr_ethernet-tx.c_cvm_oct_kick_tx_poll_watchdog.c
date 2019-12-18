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
struct TYPE_2__ {int one_shot; int /*<<< orphan*/  len; } ;
union cvmx_ciu_timx {scalar_t__ u64; TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_TIMX (int) ; 
 int /*<<< orphan*/  cvm_oct_tx_poll_interval ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cvm_oct_kick_tx_poll_watchdog(void)
{
	union cvmx_ciu_timx ciu_timx;

	ciu_timx.u64 = 0;
	ciu_timx.s.one_shot = 1;
	ciu_timx.s.len = cvm_oct_tx_poll_interval;
	cvmx_write_csr(CVMX_CIU_TIMX(1), ciu_timx.u64);
}