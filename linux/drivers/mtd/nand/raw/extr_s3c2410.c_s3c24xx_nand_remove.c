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
struct s3c2410_nand_mtd {int /*<<< orphan*/  chip; } ;
struct s3c2410_nand_info {int mtd_count; int /*<<< orphan*/  clk; struct s3c2410_nand_mtd* mtds; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_DISABLE ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int,struct s3c2410_nand_mtd*) ; 
 int /*<<< orphan*/  s3c2410_nand_clk_set_state (struct s3c2410_nand_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c2410_nand_cpufreq_deregister (struct s3c2410_nand_info*) ; 
 struct s3c2410_nand_info* to_nand_info (struct platform_device*) ; 

__attribute__((used)) static int s3c24xx_nand_remove(struct platform_device *pdev)
{
	struct s3c2410_nand_info *info = to_nand_info(pdev);

	if (info == NULL)
		return 0;

	s3c2410_nand_cpufreq_deregister(info);

	/* Release all our mtds  and their partitions, then go through
	 * freeing the resources used
	 */

	if (info->mtds != NULL) {
		struct s3c2410_nand_mtd *ptr = info->mtds;
		int mtdno;

		for (mtdno = 0; mtdno < info->mtd_count; mtdno++, ptr++) {
			pr_debug("releasing mtd %d (%p)\n", mtdno, ptr);
			nand_release(&ptr->chip);
		}
	}

	/* free the common resources */

	if (!IS_ERR(info->clk))
		s3c2410_nand_clk_set_state(info, CLOCK_DISABLE);

	return 0;
}