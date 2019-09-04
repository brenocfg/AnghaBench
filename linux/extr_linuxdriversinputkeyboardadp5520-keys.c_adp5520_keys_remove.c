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
struct platform_device {int dummy; } ;
struct adp5520_keys {int /*<<< orphan*/  notifier; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int ADP5520_KP_IEN ; 
 int ADP5520_KR_IEN ; 
 int /*<<< orphan*/  adp5520_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct adp5520_keys* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int adp5520_keys_remove(struct platform_device *pdev)
{
	struct adp5520_keys *dev = platform_get_drvdata(pdev);

	adp5520_unregister_notifier(dev->master, &dev->notifier,
				ADP5520_KP_IEN | ADP5520_KR_IEN);

	return 0;
}