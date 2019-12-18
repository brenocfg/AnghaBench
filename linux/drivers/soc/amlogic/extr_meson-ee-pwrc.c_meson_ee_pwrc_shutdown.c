#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_power ) (struct meson_ee_pwrc_domain*) ;} ;
struct meson_ee_pwrc_domain {int /*<<< orphan*/  base; TYPE_2__ desc; } ;
struct TYPE_3__ {int num_domains; } ;
struct meson_ee_pwrc {struct meson_ee_pwrc_domain* domains; TYPE_1__ xlate; } ;

/* Variables and functions */
 int /*<<< orphan*/  meson_ee_pwrc_off (int /*<<< orphan*/ *) ; 
 struct meson_ee_pwrc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct meson_ee_pwrc_domain*) ; 

__attribute__((used)) static void meson_ee_pwrc_shutdown(struct platform_device *pdev)
{
	struct meson_ee_pwrc *pwrc = platform_get_drvdata(pdev);
	int i;

	for (i = 0 ; i < pwrc->xlate.num_domains ; ++i) {
		struct meson_ee_pwrc_domain *dom = &pwrc->domains[i];

		if (dom->desc.get_power && !dom->desc.get_power(dom))
			meson_ee_pwrc_off(&dom->base);
	}
}