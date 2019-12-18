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
struct vpfe_ccdc_config_params_raw {int dummy; } ;
struct TYPE_3__ {struct vpfe_ccdc_config_params_raw config_params; } ;
struct TYPE_4__ {TYPE_1__ bayer; } ;
struct vpfe_ccdc {TYPE_2__ ccdc_cfg; } ;

/* Variables and functions */

__attribute__((used)) static void
vpfe_ccdc_update_raw_params(struct vpfe_ccdc *ccdc,
			    struct vpfe_ccdc_config_params_raw *raw_params)
{
	struct vpfe_ccdc_config_params_raw *config_params =
				&ccdc->ccdc_cfg.bayer.config_params;

	*config_params = *raw_params;
}