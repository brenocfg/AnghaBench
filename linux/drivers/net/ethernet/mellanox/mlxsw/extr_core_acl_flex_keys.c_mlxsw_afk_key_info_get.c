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
struct mlxsw_afk_key_info {int /*<<< orphan*/  ref_count; } ;
struct mlxsw_afk_element_usage {int dummy; } ;
struct mlxsw_afk {int dummy; } ;

/* Variables and functions */
 struct mlxsw_afk_key_info* mlxsw_afk_key_info_create (struct mlxsw_afk*,struct mlxsw_afk_element_usage*) ; 
 struct mlxsw_afk_key_info* mlxsw_afk_key_info_find (struct mlxsw_afk*,struct mlxsw_afk_element_usage*) ; 

struct mlxsw_afk_key_info *
mlxsw_afk_key_info_get(struct mlxsw_afk *mlxsw_afk,
		       struct mlxsw_afk_element_usage *elusage)
{
	struct mlxsw_afk_key_info *key_info;

	key_info = mlxsw_afk_key_info_find(mlxsw_afk, elusage);
	if (key_info) {
		key_info->ref_count++;
		return key_info;
	}
	return mlxsw_afk_key_info_create(mlxsw_afk, elusage);
}