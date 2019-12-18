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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_ritr_sp_if_lag_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_ritr_sp_if_system_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ritr_sp_if_vid_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_reg_ritr_sp_if_pack(char *payload, bool lag,
					     u16 system_port, u16 vid)
{
	mlxsw_reg_ritr_sp_if_lag_set(payload, lag);
	mlxsw_reg_ritr_sp_if_system_port_set(payload, system_port);
	mlxsw_reg_ritr_sp_if_vid_set(payload, vid);
}