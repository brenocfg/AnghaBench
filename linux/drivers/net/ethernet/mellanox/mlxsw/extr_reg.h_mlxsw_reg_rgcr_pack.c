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
 int /*<<< orphan*/  mlxsw_reg_rgcr_ipv4_en_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_rgcr_ipv6_en_set (char*,int) ; 
 int /*<<< orphan*/  rgcr ; 

__attribute__((used)) static inline void mlxsw_reg_rgcr_pack(char *payload, bool ipv4_en,
				       bool ipv6_en)
{
	MLXSW_REG_ZERO(rgcr, payload);
	mlxsw_reg_rgcr_ipv4_en_set(payload, ipv4_en);
	mlxsw_reg_rgcr_ipv6_en_set(payload, ipv6_en);
}