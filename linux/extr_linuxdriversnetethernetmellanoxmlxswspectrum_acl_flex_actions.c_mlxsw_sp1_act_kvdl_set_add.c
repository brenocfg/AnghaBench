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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int mlxsw_sp_act_kvdl_set_add (void*,int /*<<< orphan*/ *,char*,int,int) ; 

__attribute__((used)) static int mlxsw_sp1_act_kvdl_set_add(void *priv, u32 *p_kvdl_index,
				      char *enc_actions, bool is_first)
{
	return mlxsw_sp_act_kvdl_set_add(priv, p_kvdl_index, enc_actions,
					 is_first, false);
}