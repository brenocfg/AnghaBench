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
 int /*<<< orphan*/  mlxsw_reg_rigr2_erif_entry_erif_set (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rigr2_erif_entry_v_set (char*,int,int) ; 

__attribute__((used)) static inline void mlxsw_reg_rigr2_erif_entry_pack(char *payload, int index,
						   bool v, u16 erif)
{
	mlxsw_reg_rigr2_erif_entry_v_set(payload, index, v);
	mlxsw_reg_rigr2_erif_entry_erif_set(payload, index, erif);
}