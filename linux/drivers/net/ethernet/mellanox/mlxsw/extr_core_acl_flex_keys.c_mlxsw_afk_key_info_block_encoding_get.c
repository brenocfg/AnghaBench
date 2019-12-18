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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_afk_key_info {TYPE_1__** blocks; } ;
struct TYPE_2__ {int /*<<< orphan*/  encoding; } ;

/* Variables and functions */

u16
mlxsw_afk_key_info_block_encoding_get(const struct mlxsw_afk_key_info *key_info,
				      int block_index)
{
	return key_info->blocks[block_index]->encoding;
}