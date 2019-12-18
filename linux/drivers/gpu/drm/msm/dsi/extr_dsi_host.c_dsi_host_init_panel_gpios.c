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
struct msm_dsi_host {void* te_gpio; void* disp_en_gpio; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int) ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsi_host_init_panel_gpios(struct msm_dsi_host *msm_host,
			struct device *panel_device)
{
	msm_host->disp_en_gpio = devm_gpiod_get_optional(panel_device,
							 "disp-enable",
							 GPIOD_OUT_LOW);
	if (IS_ERR(msm_host->disp_en_gpio)) {
		DBG("cannot get disp-enable-gpios %ld",
				PTR_ERR(msm_host->disp_en_gpio));
		return PTR_ERR(msm_host->disp_en_gpio);
	}

	msm_host->te_gpio = devm_gpiod_get_optional(panel_device, "disp-te",
								GPIOD_IN);
	if (IS_ERR(msm_host->te_gpio)) {
		DBG("cannot get disp-te-gpios %ld", PTR_ERR(msm_host->te_gpio));
		return PTR_ERR(msm_host->te_gpio);
	}

	return 0;
}