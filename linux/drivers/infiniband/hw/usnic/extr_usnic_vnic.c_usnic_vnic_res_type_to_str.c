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
typedef  enum usnic_vnic_res_type { ____Placeholder_usnic_vnic_res_type } usnic_vnic_res_type ;

/* Variables and functions */
#define  USNIC_VNIC_RES_TYPES 128 
 int USNIC_VNIC_RES_TYPE_MAX ; 

const char *usnic_vnic_res_type_to_str(enum usnic_vnic_res_type res_type)
{
#define DEFINE_USNIC_VNIC_RES_AT(usnic_vnic_res_t, vnic_res_type, desc, val) \
		desc,
#define DEFINE_USNIC_VNIC_RES(usnic_vnic_res_t, vnic_res_type, desc) \
		desc,
	static const char * const usnic_vnic_res_type_desc[] = {
						USNIC_VNIC_RES_TYPES};
#undef DEFINE_USNIC_VNIC_RES
#undef DEFINE_USNIC_VNIC_RES_AT

	if (res_type >= USNIC_VNIC_RES_TYPE_MAX)
		return "unknown";

	return usnic_vnic_res_type_desc[res_type];

}