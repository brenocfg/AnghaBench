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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_item {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  key; } ;
struct mlxsw_afk_element_values {int /*<<< orphan*/  elusage; TYPE_1__ storage; } ;
struct mlxsw_afk_element_info {scalar_t__ type; struct mlxsw_item item; } ;
typedef  enum mlxsw_afk_element { ____Placeholder_mlxsw_afk_element } mlxsw_afk_element ;

/* Variables and functions */
 scalar_t__ MLXSW_AFK_ELEMENT_TYPE_U32 ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __mlxsw_item_set32 (int /*<<< orphan*/ ,struct mlxsw_item const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlxsw_afk_element_info* mlxsw_afk_element_infos ; 
 int /*<<< orphan*/  mlxsw_afk_element_usage_add (int /*<<< orphan*/ *,int) ; 

void mlxsw_afk_values_add_u32(struct mlxsw_afk_element_values *values,
			      enum mlxsw_afk_element element,
			      u32 key_value, u32 mask_value)
{
	const struct mlxsw_afk_element_info *elinfo =
				&mlxsw_afk_element_infos[element];
	const struct mlxsw_item *storage_item = &elinfo->item;

	if (!mask_value)
		return;
	if (WARN_ON(elinfo->type != MLXSW_AFK_ELEMENT_TYPE_U32))
		return;
	__mlxsw_item_set32(values->storage.key, storage_item, 0, key_value);
	__mlxsw_item_set32(values->storage.mask, storage_item, 0, mask_value);
	mlxsw_afk_element_usage_add(&values->elusage, element);
}