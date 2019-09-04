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

/* Variables and functions */
 int /*<<< orphan*/  PWRCR ; 
 int PWRCR_PDWNACK ; 
 int PWRCR_PDWNREQ ; 
 int /*<<< orphan*/  cpu_sleep () ; 
 int fpga_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpga_write_reg (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdk7786_power_off(void)
{
	fpga_write_reg(fpga_read_reg(PWRCR) | PWRCR_PDWNREQ, PWRCR);

	/*
	 * It can take up to 20us for the R8C to do its job, back off and
	 * wait a bit until we've been shut off. Even though newer FPGA
	 * versions don't set the ACK bit, the latency issue remains.
	 */
	while ((fpga_read_reg(PWRCR) & PWRCR_PDWNACK) == 0)
		cpu_sleep();
}