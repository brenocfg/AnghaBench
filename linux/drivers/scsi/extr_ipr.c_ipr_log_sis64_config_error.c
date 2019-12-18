#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ipr_ioa_cfg {int dummy; } ;
struct ipr_hostrcb_type_23_error {struct ipr_hostrcb64_device_data_entry_enhanced* dev; int /*<<< orphan*/  errors_detected; int /*<<< orphan*/  errors_logged; } ;
struct ipr_hostrcb64_device_data_entry_enhanced {int /*<<< orphan*/  cfc_last_with_dev_vpd; int /*<<< orphan*/  ioa_last_with_dev_vpd; int /*<<< orphan*/  new_vpd; int /*<<< orphan*/  vpd; int /*<<< orphan*/  res_path; } ;
struct TYPE_5__ {struct ipr_hostrcb_type_23_error type_23_error; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
struct TYPE_7__ {TYPE_2__ error64; } ;
struct TYPE_8__ {TYPE_3__ u; } ;
struct ipr_hostrcb {TYPE_4__ hcam; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int IPR_MAX_RES_PATH_LENGTH ; 
 int /*<<< orphan*/  __ipr_format_res_path (int /*<<< orphan*/ ,char*,int) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_err (char*,...) ; 
 int /*<<< orphan*/  ipr_err_separator ; 
 int /*<<< orphan*/  ipr_log_ext_vpd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipr_log_sis64_config_error(struct ipr_ioa_cfg *ioa_cfg,
				       struct ipr_hostrcb *hostrcb)
{
	int errors_logged, i;
	struct ipr_hostrcb64_device_data_entry_enhanced *dev_entry;
	struct ipr_hostrcb_type_23_error *error;
	char buffer[IPR_MAX_RES_PATH_LENGTH];

	error = &hostrcb->hcam.u.error64.u.type_23_error;
	errors_logged = be32_to_cpu(error->errors_logged);

	ipr_err("Device Errors Detected/Logged: %d/%d\n",
		be32_to_cpu(error->errors_detected), errors_logged);

	dev_entry = error->dev;

	for (i = 0; i < errors_logged; i++, dev_entry++) {
		ipr_err_separator;

		ipr_err("Device %d : %s", i + 1,
			__ipr_format_res_path(dev_entry->res_path,
					      buffer, sizeof(buffer)));
		ipr_log_ext_vpd(&dev_entry->vpd);

		ipr_err("-----New Device Information-----\n");
		ipr_log_ext_vpd(&dev_entry->new_vpd);

		ipr_err("Cache Directory Card Information:\n");
		ipr_log_ext_vpd(&dev_entry->ioa_last_with_dev_vpd);

		ipr_err("Adapter Card Information:\n");
		ipr_log_ext_vpd(&dev_entry->cfc_last_with_dev_vpd);
	}
}