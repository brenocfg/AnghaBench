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
struct lcs_card {TYPE_1__* dev; struct ccwgroup_device* gdev; } ;
struct ccwgroup_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LCS_RECOVERY_THREAD ; 
 int __lcs_shutdown_device (struct ccwgroup_device*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lcs_clear_thread_running_bit (struct lcs_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcs_do_run_thread (struct lcs_card*,int /*<<< orphan*/ ) ; 
 int lcs_new_device (struct ccwgroup_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static int
lcs_recovery(void *ptr)
{
	struct lcs_card *card;
	struct ccwgroup_device *gdev;
        int rc;

	card = (struct lcs_card *) ptr;

	LCS_DBF_TEXT(4, trace, "recover1");
	if (!lcs_do_run_thread(card, LCS_RECOVERY_THREAD))
		return 0;
	LCS_DBF_TEXT(4, trace, "recover2");
	gdev = card->gdev;
	dev_warn(&gdev->dev,
		"A recovery process has been started for the LCS device\n");
	rc = __lcs_shutdown_device(gdev, 1);
	rc = lcs_new_device(gdev);
	if (!rc)
		pr_info("Device %s successfully recovered!\n",
			card->dev->name);
	else
		pr_info("Device %s could not be recovered!\n",
			card->dev->name);
	lcs_clear_thread_running_bit(card, LCS_RECOVERY_THREAD);
	return 0;
}