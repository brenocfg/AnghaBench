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
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ritr_rif_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ritr ; 

__attribute__((used)) static inline void mlxsw_reg_ritr_rif_pack(char *payload, u16 rif)
{
	MLXSW_REG_ZERO(ritr, payload);
	mlxsw_reg_ritr_rif_set(payload, rif);
}