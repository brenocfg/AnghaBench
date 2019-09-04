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
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_100000baseKR4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_100000baseLR4_ER4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_100000baseSR4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseKR_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseKX_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_20000baseKR2_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_25000baseCR_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_25000baseKR_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_25000baseSR_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_40000baseLR4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_40000baseSR4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_50000baseCR2_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_50000baseKR2_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_50000baseSR2_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_56000baseKR4_Full_BIT ; 
 int /*<<< orphan*/  MLX5E_1000BASE_CX_SGMII ; 
 int /*<<< orphan*/  MLX5E_1000BASE_KX ; 
 int /*<<< orphan*/  MLX5E_100GBASE_CR4 ; 
 int /*<<< orphan*/  MLX5E_100GBASE_KR4 ; 
 int /*<<< orphan*/  MLX5E_100GBASE_LR4 ; 
 int /*<<< orphan*/  MLX5E_100GBASE_SR4 ; 
 int /*<<< orphan*/  MLX5E_10GBASE_CR ; 
 int /*<<< orphan*/  MLX5E_10GBASE_CX4 ; 
 int /*<<< orphan*/  MLX5E_10GBASE_ER ; 
 int /*<<< orphan*/  MLX5E_10GBASE_KR ; 
 int /*<<< orphan*/  MLX5E_10GBASE_KX4 ; 
 int /*<<< orphan*/  MLX5E_10GBASE_SR ; 
 int /*<<< orphan*/  MLX5E_10GBASE_T ; 
 int /*<<< orphan*/  MLX5E_20GBASE_KR2 ; 
 int /*<<< orphan*/  MLX5E_25GBASE_CR ; 
 int /*<<< orphan*/  MLX5E_25GBASE_KR ; 
 int /*<<< orphan*/  MLX5E_25GBASE_SR ; 
 int /*<<< orphan*/  MLX5E_40GBASE_CR4 ; 
 int /*<<< orphan*/  MLX5E_40GBASE_KR4 ; 
 int /*<<< orphan*/  MLX5E_40GBASE_LR4 ; 
 int /*<<< orphan*/  MLX5E_40GBASE_SR4 ; 
 int /*<<< orphan*/  MLX5E_50GBASE_CR2 ; 
 int /*<<< orphan*/  MLX5E_50GBASE_KR2 ; 
 int /*<<< orphan*/  MLX5E_50GBASE_SR2 ; 
 int /*<<< orphan*/  MLX5E_56GBASE_R4 ; 
 int /*<<< orphan*/  MLX5_BUILD_PTYS2ETHTOOL_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mlx5e_build_ptys2ethtool_map(void)
{
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_1000BASE_CX_SGMII,
				       ETHTOOL_LINK_MODE_1000baseKX_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_1000BASE_KX,
				       ETHTOOL_LINK_MODE_1000baseKX_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_10GBASE_CX4,
				       ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_10GBASE_KX4,
				       ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_10GBASE_KR,
				       ETHTOOL_LINK_MODE_10000baseKR_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_20GBASE_KR2,
				       ETHTOOL_LINK_MODE_20000baseKR2_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_40GBASE_CR4,
				       ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_40GBASE_KR4,
				       ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_56GBASE_R4,
				       ETHTOOL_LINK_MODE_56000baseKR4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_10GBASE_CR,
				       ETHTOOL_LINK_MODE_10000baseKR_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_10GBASE_SR,
				       ETHTOOL_LINK_MODE_10000baseKR_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_10GBASE_ER,
				       ETHTOOL_LINK_MODE_10000baseKR_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_40GBASE_SR4,
				       ETHTOOL_LINK_MODE_40000baseSR4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_40GBASE_LR4,
				       ETHTOOL_LINK_MODE_40000baseLR4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_50GBASE_SR2,
				       ETHTOOL_LINK_MODE_50000baseSR2_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_100GBASE_CR4,
				       ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_100GBASE_SR4,
				       ETHTOOL_LINK_MODE_100000baseSR4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_100GBASE_KR4,
				       ETHTOOL_LINK_MODE_100000baseKR4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_100GBASE_LR4,
				       ETHTOOL_LINK_MODE_100000baseLR4_ER4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_10GBASE_T,
				       ETHTOOL_LINK_MODE_10000baseT_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_25GBASE_CR,
				       ETHTOOL_LINK_MODE_25000baseCR_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_25GBASE_KR,
				       ETHTOOL_LINK_MODE_25000baseKR_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_25GBASE_SR,
				       ETHTOOL_LINK_MODE_25000baseSR_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_50GBASE_CR2,
				       ETHTOOL_LINK_MODE_50000baseCR2_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_50GBASE_KR2,
				       ETHTOOL_LINK_MODE_50000baseKR2_Full_BIT);
}