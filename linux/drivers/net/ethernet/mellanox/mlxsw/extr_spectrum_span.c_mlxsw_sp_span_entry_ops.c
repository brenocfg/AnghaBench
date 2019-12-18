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
struct net_device {int dummy; } ;
struct mlxsw_sp_span_entry_ops {scalar_t__ (* can_handle ) (struct net_device const*) ;} ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct mlxsw_sp_span_entry_ops const**) ; 
 struct mlxsw_sp_span_entry_ops const** mlxsw_sp_span_entry_types ; 
 scalar_t__ stub1 (struct net_device const*) ; 

__attribute__((used)) static const struct mlxsw_sp_span_entry_ops *
mlxsw_sp_span_entry_ops(struct mlxsw_sp *mlxsw_sp,
			const struct net_device *to_dev)
{
	size_t i;

	for (i = 0; i < ARRAY_SIZE(mlxsw_sp_span_entry_types); ++i)
		if (mlxsw_sp_span_entry_types[i]->can_handle(to_dev))
			return mlxsw_sp_span_entry_types[i];

	return NULL;
}