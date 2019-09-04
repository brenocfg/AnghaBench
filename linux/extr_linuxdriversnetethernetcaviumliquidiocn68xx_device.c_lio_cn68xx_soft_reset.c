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
 int /*<<< orphan*/  lio_cn68xx_set_dpi_regs (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_cn6xxx_soft_reset (struct octeon_device*) ; 

__attribute__((used)) static int lio_cn68xx_soft_reset(struct octeon_device *oct)
{
	lio_cn6xxx_soft_reset(oct);
	lio_cn68xx_set_dpi_regs(oct);

	return 0;
}