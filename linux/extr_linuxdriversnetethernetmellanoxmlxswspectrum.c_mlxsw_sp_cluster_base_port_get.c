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
typedef  int u8 ;

/* Variables and functions */
 int MLXSW_SP_PORTS_PER_CLUSTER_MAX ; 

__attribute__((used)) static u8 mlxsw_sp_cluster_base_port_get(u8 local_port)
{
	u8 offset = (local_port - 1) % MLXSW_SP_PORTS_PER_CLUSTER_MAX;

	return local_port - offset;
}