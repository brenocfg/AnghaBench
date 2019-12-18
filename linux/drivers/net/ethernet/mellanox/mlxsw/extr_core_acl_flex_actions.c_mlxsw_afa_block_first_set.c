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
struct mlxsw_afa_block {TYPE_2__* first_set; } ;
struct TYPE_3__ {char* enc_actions; } ;
struct TYPE_4__ {TYPE_1__ ht_key; } ;

/* Variables and functions */

char *mlxsw_afa_block_first_set(struct mlxsw_afa_block *block)
{
	return block->first_set->ht_key.enc_actions;
}