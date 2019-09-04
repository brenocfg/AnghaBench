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
struct vf610_nfc {int /*<<< orphan*/  clk; } ;
struct platform_device {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct vf610_nfc* mtd_to_nfc (struct mtd_info*) ; 
 int /*<<< orphan*/  nand_release (struct mtd_info*) ; 
 struct mtd_info* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int vf610_nfc_remove(struct platform_device *pdev)
{
	struct mtd_info *mtd = platform_get_drvdata(pdev);
	struct vf610_nfc *nfc = mtd_to_nfc(mtd);

	nand_release(mtd);
	clk_disable_unprepare(nfc->clk);
	return 0;
}