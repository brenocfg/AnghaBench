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
struct s3c2410_nand_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int allow_clk_suspend(struct s3c2410_nand_info *info)
{
#ifdef CONFIG_MTD_NAND_S3C2410_CLKSTOP
	return 1;
#else
	return 0;
#endif
}