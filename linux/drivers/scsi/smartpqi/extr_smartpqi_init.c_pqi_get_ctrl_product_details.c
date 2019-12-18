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
struct pqi_ctrl_info {char* firmware_version; char* model; char* vendor; } ;
struct bmic_identify_controller {int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  product_id; int /*<<< orphan*/  firmware_build_number; int /*<<< orphan*/  firmware_version; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct bmic_identify_controller*) ; 
 struct bmic_identify_controller* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int pqi_identify_controller (struct pqi_ctrl_info*,struct bmic_identify_controller*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static int pqi_get_ctrl_product_details(struct pqi_ctrl_info *ctrl_info)
{
	int rc;
	struct bmic_identify_controller *identify;

	identify = kmalloc(sizeof(*identify), GFP_KERNEL);
	if (!identify)
		return -ENOMEM;

	rc = pqi_identify_controller(ctrl_info, identify);
	if (rc)
		goto out;

	memcpy(ctrl_info->firmware_version, identify->firmware_version,
		sizeof(identify->firmware_version));
	ctrl_info->firmware_version[sizeof(identify->firmware_version)] = '\0';
	snprintf(ctrl_info->firmware_version +
		strlen(ctrl_info->firmware_version),
		sizeof(ctrl_info->firmware_version),
		"-%u", get_unaligned_le16(&identify->firmware_build_number));

	memcpy(ctrl_info->model, identify->product_id,
		sizeof(identify->product_id));
	ctrl_info->model[sizeof(identify->product_id)] = '\0';

	memcpy(ctrl_info->vendor, identify->vendor_id,
		sizeof(identify->vendor_id));
	ctrl_info->vendor[sizeof(identify->vendor_id)] = '\0';

out:
	kfree(identify);

	return rc;
}