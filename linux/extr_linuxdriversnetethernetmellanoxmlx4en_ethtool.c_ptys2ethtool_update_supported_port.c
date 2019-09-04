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
typedef  int u32 ;
struct mlx4_ptys_reg {int /*<<< orphan*/  eth_proto_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Backplane_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_FIBRE_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_TP_BIT ; 
 int /*<<< orphan*/  MLX4_1000BASE_CX_SGMII ; 
 int /*<<< orphan*/  MLX4_1000BASE_KX ; 
 int /*<<< orphan*/  MLX4_1000BASE_T ; 
 int /*<<< orphan*/  MLX4_100BASE_TX ; 
 int /*<<< orphan*/  MLX4_10GBASE_CR ; 
 int /*<<< orphan*/  MLX4_10GBASE_KR ; 
 int /*<<< orphan*/  MLX4_10GBASE_KX4 ; 
 int /*<<< orphan*/  MLX4_10GBASE_SR ; 
 int /*<<< orphan*/  MLX4_10GBASE_T ; 
 int /*<<< orphan*/  MLX4_20GBASE_KR2 ; 
 int /*<<< orphan*/  MLX4_40GBASE_CR4 ; 
 int /*<<< orphan*/  MLX4_40GBASE_KR4 ; 
 int /*<<< orphan*/  MLX4_40GBASE_SR4 ; 
 int /*<<< orphan*/  MLX4_56GBASE_KR4 ; 
 int /*<<< orphan*/  MLX4_56GBASE_SR4 ; 
 int MLX4_PROT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ptys2ethtool_update_supported_port(unsigned long *mask,
					       struct mlx4_ptys_reg *ptys_reg)
{
	u32 eth_proto = be32_to_cpu(ptys_reg->eth_proto_cap);

	if (eth_proto & (MLX4_PROT_MASK(MLX4_10GBASE_T)
			 | MLX4_PROT_MASK(MLX4_1000BASE_T)
			 | MLX4_PROT_MASK(MLX4_100BASE_TX))) {
		__set_bit(ETHTOOL_LINK_MODE_TP_BIT, mask);
	} else if (eth_proto & (MLX4_PROT_MASK(MLX4_10GBASE_CR)
			 | MLX4_PROT_MASK(MLX4_10GBASE_SR)
			 | MLX4_PROT_MASK(MLX4_56GBASE_SR4)
			 | MLX4_PROT_MASK(MLX4_40GBASE_CR4)
			 | MLX4_PROT_MASK(MLX4_40GBASE_SR4)
			 | MLX4_PROT_MASK(MLX4_1000BASE_CX_SGMII))) {
		__set_bit(ETHTOOL_LINK_MODE_FIBRE_BIT, mask);
	} else if (eth_proto & (MLX4_PROT_MASK(MLX4_56GBASE_KR4)
			 | MLX4_PROT_MASK(MLX4_40GBASE_KR4)
			 | MLX4_PROT_MASK(MLX4_20GBASE_KR2)
			 | MLX4_PROT_MASK(MLX4_10GBASE_KR)
			 | MLX4_PROT_MASK(MLX4_10GBASE_KX4)
			 | MLX4_PROT_MASK(MLX4_1000BASE_KX))) {
		__set_bit(ETHTOOL_LINK_MODE_Backplane_BIT, mask);
	}
}