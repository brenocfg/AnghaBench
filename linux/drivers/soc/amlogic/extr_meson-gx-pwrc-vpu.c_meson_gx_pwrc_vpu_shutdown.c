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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* power_off ) (TYPE_1__*) ;} ;
struct meson_gx_pwrc_vpu {TYPE_1__ genpd; } ;

/* Variables and functions */
 int meson_gx_pwrc_vpu_get_power (struct meson_gx_pwrc_vpu*) ; 
 struct meson_gx_pwrc_vpu* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void meson_gx_pwrc_vpu_shutdown(struct platform_device *pdev)
{
	struct meson_gx_pwrc_vpu *vpu_pd = platform_get_drvdata(pdev);
	bool powered_off;

	powered_off = meson_gx_pwrc_vpu_get_power(vpu_pd);
	if (!powered_off)
		vpu_pd->genpd.power_off(&vpu_pd->genpd);
}