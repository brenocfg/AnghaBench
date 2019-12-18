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
struct venus_core {scalar_t__ use_tz; TYPE_1__* res; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  fwname; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_QCOM_MDT_LOADER ; 
 int EINVAL ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VENUS_PAS_ID ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  qcom_scm_is_available () ; 
 int qcom_scm_pas_auth_and_reset (int /*<<< orphan*/ ) ; 
 int venus_boot_no_tz (struct venus_core*,int /*<<< orphan*/ ,size_t) ; 
 int venus_load_fw (struct venus_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 

int venus_boot(struct venus_core *core)
{
	struct device *dev = core->dev;
	phys_addr_t mem_phys;
	size_t mem_size;
	int ret;

	if (!IS_ENABLED(CONFIG_QCOM_MDT_LOADER) ||
	    (core->use_tz && !qcom_scm_is_available()))
		return -EPROBE_DEFER;

	ret = venus_load_fw(core, core->res->fwname, &mem_phys, &mem_size);
	if (ret) {
		dev_err(dev, "fail to load video firmware\n");
		return -EINVAL;
	}

	if (core->use_tz)
		ret = qcom_scm_pas_auth_and_reset(VENUS_PAS_ID);
	else
		ret = venus_boot_no_tz(core, mem_phys, mem_size);

	return ret;
}