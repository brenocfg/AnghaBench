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
struct aem_ipmi_data {int /*<<< orphan*/  bmc_device; } ;
struct aem_find_instance_resp {int major; int /*<<< orphan*/  module_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  aem_find_aem2 (struct aem_ipmi_data*,struct aem_find_instance_resp*,int) ; 
 int aem_init_aem2_inst (struct aem_ipmi_data*,struct aem_find_instance_resp*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static void aem_init_aem2(struct aem_ipmi_data *probe)
{
	struct aem_find_instance_resp fi_resp;
	int err;
	int i = 0;

	while (!aem_find_aem2(probe, &fi_resp, i)) {
		if (fi_resp.major != 2) {
			dev_err(probe->bmc_device,
				"Unknown AEM v%d; please report this to the maintainer.\n",
				fi_resp.major);
			i++;
			continue;
		}
		err = aem_init_aem2_inst(probe, &fi_resp);
		if (err) {
			dev_err(probe->bmc_device,
				"Error %d initializing AEM2 0x%X\n",
				err, fi_resp.module_handle);
		}
		i++;
	}
}