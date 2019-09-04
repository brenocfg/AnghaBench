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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct cros_ec_keyb {int /*<<< orphan*/  notifier; TYPE_1__* ec; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_notifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  blocking_notifier_chain_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct cros_ec_keyb* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cros_ec_keyb_remove(struct platform_device *pdev)
{
	struct cros_ec_keyb *ckdev = dev_get_drvdata(&pdev->dev);

	blocking_notifier_chain_unregister(&ckdev->ec->event_notifier,
					   &ckdev->notifier);

	return 0;
}