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

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_sbsr_clr_set (char*,int) ; 
 int /*<<< orphan*/  sbsr ; 

__attribute__((used)) static inline void mlxsw_reg_sbsr_pack(char *payload, bool clr)
{
	MLXSW_REG_ZERO(sbsr, payload);
	mlxsw_reg_sbsr_clr_set(payload, clr);
}