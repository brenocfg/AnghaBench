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
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int mlxsw_sp_setup_tc_block_cb_matchall (int,void*,void*,int) ; 

__attribute__((used)) static int mlxsw_sp_setup_tc_block_cb_matchall_eg(enum tc_setup_type type,
						  void *type_data,
						  void *cb_priv)
{
	return mlxsw_sp_setup_tc_block_cb_matchall(type, type_data,
						   cb_priv, false);
}