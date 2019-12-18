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
 int MLXSW_REG_RECR2_IPV4_SIP0 ; 
 int MLXSW_REG_RECR2_IPV4_SIP3 ; 
 int /*<<< orphan*/  mlxsw_reg_recr2_outer_header_fields_enable_set (char*,int,int) ; 

__attribute__((used)) static inline void mlxsw_reg_recr2_ipv4_sip_enable(char *payload)
{
	int i;

	for (i = MLXSW_REG_RECR2_IPV4_SIP0; i <= MLXSW_REG_RECR2_IPV4_SIP3; i++)
		mlxsw_reg_recr2_outer_header_fields_enable_set(payload, i,
							       true);
}