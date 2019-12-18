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
struct meson_ao_cec_device {int /*<<< orphan*/  adap; int /*<<< orphan*/  notify; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  cec_notifier_cec_adap_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_unregister_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct meson_ao_cec_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int meson_ao_cec_remove(struct platform_device *pdev)
{
	struct meson_ao_cec_device *ao_cec = platform_get_drvdata(pdev);

	clk_disable_unprepare(ao_cec->core);

	cec_notifier_cec_adap_unregister(ao_cec->notify);
	cec_unregister_adapter(ao_cec->adap);

	return 0;
}