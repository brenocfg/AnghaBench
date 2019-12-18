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
typedef  scalar_t__ u32 ;
struct mlxsw_item {int dummy; } ;

/* Variables and functions */
 scalar_t__ __mlxsw_item_get32 (char*,struct mlxsw_item const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mlxsw_item_set32 (char*,struct mlxsw_item const*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mlxsw_sp_afk_encode_u32(const struct mlxsw_item *storage_item,
				    const struct mlxsw_item *output_item,
				    char *storage, char *output, int diff)
{
	u32 value;

	value = __mlxsw_item_get32(storage, storage_item, 0);
	__mlxsw_item_set32(output, output_item, 0, value + diff);
}