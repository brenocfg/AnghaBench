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
struct TYPE_3__ {unsigned int bytes; } ;
struct mlxsw_item {TYPE_1__ size; } ;
struct TYPE_4__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  key; } ;
struct mlxsw_afk_element_values {int /*<<< orphan*/  elusage; TYPE_2__ storage; } ;
struct mlxsw_afk_element_info {scalar_t__ type; struct mlxsw_item item; } ;
typedef  enum mlxsw_afk_element { ____Placeholder_mlxsw_afk_element } mlxsw_afk_element ;

/* Variables and functions */
 scalar_t__ MLXSW_AFK_ELEMENT_TYPE_BUF ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __mlxsw_item_memcpy_to (int /*<<< orphan*/ ,char const*,struct mlxsw_item const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memchr_inv (char const*,int /*<<< orphan*/ ,unsigned int) ; 
 struct mlxsw_afk_element_info* mlxsw_afk_element_infos ; 
 int /*<<< orphan*/  mlxsw_afk_element_usage_add (int /*<<< orphan*/ *,int) ; 

void mlxsw_afk_values_add_buf(struct mlxsw_afk_element_values *values,
			      enum mlxsw_afk_element element,
			      const char *key_value, const char *mask_value,
			      unsigned int len)
{
	const struct mlxsw_afk_element_info *elinfo =
				&mlxsw_afk_element_infos[element];
	const struct mlxsw_item *storage_item = &elinfo->item;

	if (!memchr_inv(mask_value, 0, len)) /* If mask is zero */
		return;
	if (WARN_ON(elinfo->type != MLXSW_AFK_ELEMENT_TYPE_BUF) ||
	    WARN_ON(elinfo->item.size.bytes != len))
		return;
	__mlxsw_item_memcpy_to(values->storage.key, key_value,
			       storage_item, 0);
	__mlxsw_item_memcpy_to(values->storage.mask, mask_value,
			       storage_item, 0);
	mlxsw_afk_element_usage_add(&values->elusage, element);
}