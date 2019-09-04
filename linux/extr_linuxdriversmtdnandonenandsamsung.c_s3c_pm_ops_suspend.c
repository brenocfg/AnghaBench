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
struct onenand_chip {int /*<<< orphan*/  (* wait ) (struct mtd_info*,int /*<<< orphan*/ ) ;} ;
struct mtd_info {struct onenand_chip* priv; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FL_PM_SUSPENDED ; 
 struct mtd_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c_pm_ops_suspend(struct device *dev)
{
	struct mtd_info *mtd = dev_get_drvdata(dev);
	struct onenand_chip *this = mtd->priv;

	this->wait(mtd, FL_PM_SUSPENDED);
	return 0;
}