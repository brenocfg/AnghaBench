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
struct pm8941_pwrkey {int /*<<< orphan*/  reboot_notifier; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct pm8941_pwrkey* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pm8941_pwrkey_remove(struct platform_device *pdev)
{
	struct pm8941_pwrkey *pwrkey = platform_get_drvdata(pdev);

	unregister_reboot_notifier(&pwrkey->reboot_notifier);

	return 0;
}