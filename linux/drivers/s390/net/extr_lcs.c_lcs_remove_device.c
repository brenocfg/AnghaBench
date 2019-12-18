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
struct lcs_card {scalar_t__ dev; } ;
struct ccwgroup_device {scalar_t__ state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CCWGROUP_ONLINE ; 
 int /*<<< orphan*/  LCS_DBF_HEX (int,int /*<<< orphan*/ ,struct lcs_card**,int) ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 struct lcs_card* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lcs_cleanup_card (struct lcs_card*) ; 
 int /*<<< orphan*/  lcs_free_card (struct lcs_card*) ; 
 int /*<<< orphan*/  lcs_shutdown_device (struct ccwgroup_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup ; 
 int /*<<< orphan*/  unregister_netdev (scalar_t__) ; 

__attribute__((used)) static void
lcs_remove_device(struct ccwgroup_device *ccwgdev)
{
	struct lcs_card *card;

	card = dev_get_drvdata(&ccwgdev->dev);
	if (!card)
		return;

	LCS_DBF_TEXT(3, setup, "remdev");
	LCS_DBF_HEX(3, setup, &card, sizeof(void*));
	if (ccwgdev->state == CCWGROUP_ONLINE) {
		lcs_shutdown_device(ccwgdev);
	}
	if (card->dev)
		unregister_netdev(card->dev);
	lcs_cleanup_card(card);
	lcs_free_card(card);
	dev_set_drvdata(&ccwgdev->dev, NULL);
	put_device(&ccwgdev->dev);
}