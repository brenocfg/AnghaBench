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
typedef  scalar_t__ u16 ;
struct mlxfw_mfa2_tlv_multi {int dummy; } ;
struct mlxfw_mfa2_tlv_component_descriptor {int dummy; } ;
struct mlxfw_mfa2_tlv {int dummy; } ;
struct mlxfw_mfa2_file {scalar_t__ component_count; int /*<<< orphan*/  first_component; } ;

/* Variables and functions */
 struct mlxfw_mfa2_tlv* mlxfw_mfa2_tlv_advance (struct mlxfw_mfa2_file const*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct mlxfw_mfa2_tlv_component_descriptor const* mlxfw_mfa2_tlv_component_descriptor_get (struct mlxfw_mfa2_file const*,struct mlxfw_mfa2_tlv const*) ; 
 struct mlxfw_mfa2_tlv* mlxfw_mfa2_tlv_multi_child (struct mlxfw_mfa2_file const*,struct mlxfw_mfa2_tlv_multi const*) ; 
 struct mlxfw_mfa2_tlv_multi* mlxfw_mfa2_tlv_multi_get (struct mlxfw_mfa2_file const*,struct mlxfw_mfa2_tlv const*) ; 

__attribute__((used)) static const struct mlxfw_mfa2_tlv_component_descriptor *
mlxfw_mfa2_file_component_tlv_get(const struct mlxfw_mfa2_file *mfa2_file,
				  u16 comp_index)
{
	const struct mlxfw_mfa2_tlv_multi *multi;
	const struct mlxfw_mfa2_tlv *multi_child;
	const struct mlxfw_mfa2_tlv *comp_tlv;

	if (comp_index > mfa2_file->component_count)
		return NULL;

	comp_tlv = mlxfw_mfa2_tlv_advance(mfa2_file, mfa2_file->first_component,
					  comp_index);
	if (!comp_tlv)
		return NULL;

	multi = mlxfw_mfa2_tlv_multi_get(mfa2_file, comp_tlv);
	if (!multi)
		return NULL;

	multi_child = mlxfw_mfa2_tlv_multi_child(mfa2_file, multi);
	if (!multi_child)
		return NULL;

	return mlxfw_mfa2_tlv_component_descriptor_get(mfa2_file, multi_child);
}