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
typedef  enum mlxsw_reg_spms_state { ____Placeholder_mlxsw_reg_spms_state } mlxsw_reg_spms_state ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_spms_state_set (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void mlxsw_reg_spms_vid_pack(char *payload, u16 vid,
					   enum mlxsw_reg_spms_state state)
{
	mlxsw_reg_spms_state_set(payload, vid, state);
}