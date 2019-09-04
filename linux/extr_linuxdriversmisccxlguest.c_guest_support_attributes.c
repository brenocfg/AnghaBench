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
typedef  enum cxl_attrs { ____Placeholder_cxl_attrs } cxl_attrs ;

/* Variables and functions */
#define  CXL_ADAPTER_ATTRS 130 
#define  CXL_AFU_ATTRS 129 
#define  CXL_AFU_MASTER_ATTRS 128 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static bool guest_support_attributes(const char *attr_name,
				     enum cxl_attrs type)
{
	switch (type) {
	case CXL_ADAPTER_ATTRS:
		if ((strcmp(attr_name, "base_image") == 0) ||
			(strcmp(attr_name, "load_image_on_perst") == 0) ||
			(strcmp(attr_name, "perst_reloads_same_image") == 0) ||
			(strcmp(attr_name, "image_loaded") == 0))
			return false;
		break;
	case CXL_AFU_MASTER_ATTRS:
		if ((strcmp(attr_name, "pp_mmio_off") == 0))
			return false;
		break;
	case CXL_AFU_ATTRS:
		break;
	default:
		break;
	}

	return true;
}