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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_pptb_prio_to_buff_msb_set (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pptb_prio_to_buff_set (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_reg_pptb_prio_to_buff_pack(char *payload, u8 prio,
						    u8 buff)
{
	mlxsw_reg_pptb_prio_to_buff_set(payload, prio, buff);
	mlxsw_reg_pptb_prio_to_buff_msb_set(payload, prio, buff);
}