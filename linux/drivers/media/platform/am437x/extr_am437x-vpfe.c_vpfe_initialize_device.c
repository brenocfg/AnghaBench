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
struct vpfe_subdev_info {int /*<<< orphan*/  sd; } ;
struct vpfe_device {size_t std_index; int /*<<< orphan*/  ccdc; int /*<<< orphan*/  pdev; scalar_t__ current_input; int /*<<< orphan*/ * sd; TYPE_1__* cfg; } ;
struct TYPE_4__ {int /*<<< orphan*/  std_id; } ;
struct TYPE_3__ {struct vpfe_subdev_info* sub_devs; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpfe_ccdc_restore_defaults (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpfe_clear_intr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vpfe_config_enable (int /*<<< orphan*/ *,int) ; 
 int vpfe_config_image_format (struct vpfe_device*,int /*<<< orphan*/ ) ; 
 TYPE_2__* vpfe_standards ; 

__attribute__((used)) static int vpfe_initialize_device(struct vpfe_device *vpfe)
{
	struct vpfe_subdev_info *sdinfo;
	int ret;

	sdinfo = &vpfe->cfg->sub_devs[0];
	sdinfo->sd = vpfe->sd[0];
	vpfe->current_input = 0;
	vpfe->std_index = 0;
	/* Configure the default format information */
	ret = vpfe_config_image_format(vpfe,
				       vpfe_standards[vpfe->std_index].std_id);
	if (ret)
		return ret;

	pm_runtime_get_sync(vpfe->pdev);

	vpfe_config_enable(&vpfe->ccdc, 1);

	vpfe_ccdc_restore_defaults(&vpfe->ccdc);

	/* Clear all VPFE interrupts */
	vpfe_clear_intr(&vpfe->ccdc, -1);

	return ret;
}