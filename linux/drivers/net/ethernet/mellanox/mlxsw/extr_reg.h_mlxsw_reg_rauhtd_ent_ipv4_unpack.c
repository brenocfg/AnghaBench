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

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_rauhtd_ipv4_ent_dip_get (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_rauhtd_ipv4_ent_rif_get (char*,int) ; 

__attribute__((used)) static inline void mlxsw_reg_rauhtd_ent_ipv4_unpack(char *payload,
						    int ent_index, u16 *p_rif,
						    u32 *p_dip)
{
	*p_rif = mlxsw_reg_rauhtd_ipv4_ent_rif_get(payload, ent_index);
	*p_dip = mlxsw_reg_rauhtd_ipv4_ent_dip_get(payload, ent_index);
}