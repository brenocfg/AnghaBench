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
struct mlxsw_sp_span_parms {int dummy; } ;

/* Variables and functions */
 int mlxsw_sp_span_entry_unoffloadable (struct mlxsw_sp_span_parms*) ; 

__attribute__((used)) static int
mlxsw_sp_span_entry_nop_parms(const struct net_device *to_dev,
			      struct mlxsw_sp_span_parms *sparmsp)
{
	return mlxsw_sp_span_entry_unoffloadable(sparmsp);
}