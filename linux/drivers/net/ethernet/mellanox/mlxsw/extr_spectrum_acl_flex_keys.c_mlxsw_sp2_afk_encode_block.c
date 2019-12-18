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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  __mlxsw_sp2_afk_block_value_set (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp2_afk_block_value_get (char*) ; 

__attribute__((used)) static void mlxsw_sp2_afk_encode_block(char *output, int block_index,
				       char *block)
{
	u64 block_value = mlxsw_sp2_afk_block_value_get(block);

	__mlxsw_sp2_afk_block_value_set(output, block_index, block_value);
}