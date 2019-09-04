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
struct stih_cec {int /*<<< orphan*/  notifier; int /*<<< orphan*/  adap; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cec_notifier_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_unregister_adapter (int /*<<< orphan*/ ) ; 
 struct stih_cec* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int stih_cec_remove(struct platform_device *pdev)
{
	struct stih_cec *cec = platform_get_drvdata(pdev);

	cec_unregister_adapter(cec->adap);
	cec_notifier_put(cec->notifier);

	return 0;
}