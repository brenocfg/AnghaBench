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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  enum mlxsw_reg_rauht_op { ____Placeholder_mlxsw_reg_rauht_op } mlxsw_reg_rauht_op ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_rauht_dip4_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rauht_pack (char*,int,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline void mlxsw_reg_rauht_pack4(char *payload,
					 enum mlxsw_reg_rauht_op op, u16 rif,
					 const char *mac, u32 dip)
{
	mlxsw_reg_rauht_pack(payload, op, rif, mac);
	mlxsw_reg_rauht_dip4_set(payload, dip);
}