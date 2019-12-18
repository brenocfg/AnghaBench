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
struct lcs_card {int dummy; } ;
struct ccwgroup_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct lcs_card* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int lcs_pm_resume (struct lcs_card*) ; 

__attribute__((used)) static int lcs_thaw(struct ccwgroup_device *gdev)
{
	struct lcs_card *card = dev_get_drvdata(&gdev->dev);
	return lcs_pm_resume(card);
}