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
struct octeon_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ cn23xx_vf_setup_global_input_regs (struct octeon_device*) ; 
 int /*<<< orphan*/  cn23xx_vf_setup_global_output_regs (struct octeon_device*) ; 

__attribute__((used)) static int cn23xx_setup_vf_device_regs(struct octeon_device *oct)
{
	if (cn23xx_vf_setup_global_input_regs(oct))
		return -1;

	cn23xx_vf_setup_global_output_regs(oct);

	return 0;
}