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
 int /*<<< orphan*/  mlxsw_reg_rauhtd_ipv6_ent_dip_memcpy_from (char*,int,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_rauhtd_ipv6_ent_rif_get (char*,int) ; 

__attribute__((used)) static inline void mlxsw_reg_rauhtd_ent_ipv6_unpack(char *payload,
						    int rec_index, u16 *p_rif,
						    char *p_dip)
{
	*p_rif = mlxsw_reg_rauhtd_ipv6_ent_rif_get(payload, rec_index);
	mlxsw_reg_rauhtd_ipv6_ent_dip_memcpy_from(payload, rec_index, p_dip);
}