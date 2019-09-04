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
typedef  int /*<<< orphan*/  guid_t ;
typedef  enum err_types { ____Placeholder_err_types } err_types ;

/* Variables and functions */
 int ERR_TYPE_BUS ; 
 int ERR_TYPE_CACHE ; 
 int ERR_TYPE_MS ; 
 int ERR_TYPE_TLB ; 
 int /*<<< orphan*/  INFO_ERR_STRUCT_TYPE_BUS ; 
 int /*<<< orphan*/  INFO_ERR_STRUCT_TYPE_CACHE ; 
 int /*<<< orphan*/  INFO_ERR_STRUCT_TYPE_MS ; 
 int /*<<< orphan*/  INFO_ERR_STRUCT_TYPE_TLB ; 
 int N_ERR_TYPES ; 
 scalar_t__ guid_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum err_types cper_get_err_type(const guid_t *err_type)
{
	if (guid_equal(err_type, &INFO_ERR_STRUCT_TYPE_CACHE))
		return ERR_TYPE_CACHE;
	else if (guid_equal(err_type, &INFO_ERR_STRUCT_TYPE_TLB))
		return ERR_TYPE_TLB;
	else if (guid_equal(err_type, &INFO_ERR_STRUCT_TYPE_BUS))
		return ERR_TYPE_BUS;
	else if (guid_equal(err_type, &INFO_ERR_STRUCT_TYPE_MS))
		return ERR_TYPE_MS;
	else
		return N_ERR_TYPES;
}