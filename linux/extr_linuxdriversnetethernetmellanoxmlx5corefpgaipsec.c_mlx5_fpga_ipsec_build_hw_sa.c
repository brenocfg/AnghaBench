#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  spi; int /*<<< orphan*/  dip; int /*<<< orphan*/  sip; } ;
struct mlx5_ifc_fpga_ipsec_sa {TYPE_1__ ipsec_sa_v1; } ;
struct mlx5_core_dev {int dummy; } ;
struct mlx5_accel_esp_xfrm_attrs {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_FPGA_IPSEC_SA_IPV6 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  mlx5_fpga_ipsec_build_hw_xfrm (struct mlx5_core_dev*,struct mlx5_accel_esp_xfrm_attrs*,struct mlx5_ifc_fpga_ipsec_sa*) ; 

__attribute__((used)) static void
mlx5_fpga_ipsec_build_hw_sa(struct mlx5_core_dev *mdev,
			    struct mlx5_accel_esp_xfrm_attrs *xfrm_attrs,
			    const __be32 saddr[4],
			    const __be32 daddr[4],
			    const __be32 spi, bool is_ipv6,
			    struct mlx5_ifc_fpga_ipsec_sa *hw_sa)
{
	mlx5_fpga_ipsec_build_hw_xfrm(mdev, xfrm_attrs, hw_sa);

	/* IPs */
	memcpy(hw_sa->ipsec_sa_v1.sip, saddr, sizeof(hw_sa->ipsec_sa_v1.sip));
	memcpy(hw_sa->ipsec_sa_v1.dip, daddr, sizeof(hw_sa->ipsec_sa_v1.dip));

	/* SPI */
	hw_sa->ipsec_sa_v1.spi = spi;

	/* flags */
	if (is_ipv6)
		hw_sa->ipsec_sa_v1.flags |= MLX5_FPGA_IPSEC_SA_IPV6;
}