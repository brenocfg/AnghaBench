#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lcs_card {TYPE_1__* dev; } ;
struct ccwgroup_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ reg_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ NETREG_UNINITIALIZED ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct lcs_card* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int register_netdev (TYPE_1__*) ; 
 int /*<<< orphan*/  setup ; 

__attribute__((used)) static int
lcs_register_netdev(struct ccwgroup_device *ccwgdev)
{
	struct lcs_card *card;

	LCS_DBF_TEXT(2, setup, "regnetdv");
	card = dev_get_drvdata(&ccwgdev->dev);
	if (card->dev->reg_state != NETREG_UNINITIALIZED)
		return 0;
	SET_NETDEV_DEV(card->dev, &ccwgdev->dev);
	return register_netdev(card->dev);
}