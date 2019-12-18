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
struct TYPE_2__ {int /*<<< orphan*/  vpss_regs_base2; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPSS_CLK_CTRL ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 TYPE_1__ oper_cfg ; 
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vpss_driver ; 

__attribute__((used)) static void vpss_exit(void)
{
	platform_driver_unregister(&vpss_driver);
	iounmap(oper_cfg.vpss_regs_base2);
	release_mem_region(VPSS_CLK_CTRL, 4);
}