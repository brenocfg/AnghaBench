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
struct softing {int /*<<< orphan*/  dpram; int /*<<< orphan*/ ** net; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct softing*) ; 
 struct softing* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  softing_card_shutdown (struct softing*) ; 
 int /*<<< orphan*/  softing_netdev_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  softing_pdev_group ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int softing_pdev_remove(struct platform_device *pdev)
{
	struct softing *card = platform_get_drvdata(pdev);
	int j;

	/* first, disable card*/
	softing_card_shutdown(card);

	for (j = 0; j < ARRAY_SIZE(card->net); ++j) {
		if (!card->net[j])
			continue;
		softing_netdev_cleanup(card->net[j]);
		card->net[j] = NULL;
	}
	sysfs_remove_group(&pdev->dev.kobj, &softing_pdev_group);

	iounmap(card->dpram);
	kfree(card);
	return 0;
}