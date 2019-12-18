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
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_tigcr_ttl_uc_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_tigcr_ttlc_set (char*,int) ; 
 int /*<<< orphan*/  tigcr ; 

__attribute__((used)) static inline void mlxsw_reg_tigcr_pack(char *payload, bool ttlc, u8 ttl_uc)
{
	MLXSW_REG_ZERO(tigcr, payload);
	mlxsw_reg_tigcr_ttlc_set(payload, ttlc);
	mlxsw_reg_tigcr_ttl_uc_set(payload, ttl_uc);
}