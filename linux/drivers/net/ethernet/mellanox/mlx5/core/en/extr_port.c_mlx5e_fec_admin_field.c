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
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fec_override_admin_100g ; 
 int /*<<< orphan*/  fec_override_admin_10g_40g ; 
 int /*<<< orphan*/  fec_override_admin_25g ; 
 int /*<<< orphan*/  fec_override_admin_50g ; 
 int /*<<< orphan*/  fec_override_admin_56g ; 
 int /*<<< orphan*/  pplm_reg ; 

__attribute__((used)) static int mlx5e_fec_admin_field(u32 *pplm,
				 u8 *fec_policy,
				 bool write,
				 u32 speed)
{
	switch (speed) {
	case 10000:
	case 40000:
		if (!write)
			*fec_policy = MLX5_GET(pplm_reg, pplm,
					       fec_override_admin_10g_40g);
		else
			MLX5_SET(pplm_reg, pplm,
				 fec_override_admin_10g_40g, *fec_policy);
		break;
	case 25000:
		if (!write)
			*fec_policy = MLX5_GET(pplm_reg, pplm,
					       fec_override_admin_25g);
		else
			MLX5_SET(pplm_reg, pplm,
				 fec_override_admin_25g, *fec_policy);
		break;
	case 50000:
		if (!write)
			*fec_policy = MLX5_GET(pplm_reg, pplm,
					       fec_override_admin_50g);
		else
			MLX5_SET(pplm_reg, pplm,
				 fec_override_admin_50g, *fec_policy);
		break;
	case 56000:
		if (!write)
			*fec_policy = MLX5_GET(pplm_reg, pplm,
					       fec_override_admin_56g);
		else
			MLX5_SET(pplm_reg, pplm,
				 fec_override_admin_56g, *fec_policy);
		break;
	case 100000:
		if (!write)
			*fec_policy = MLX5_GET(pplm_reg, pplm,
					       fec_override_admin_100g);
		else
			MLX5_SET(pplm_reg, pplm,
				 fec_override_admin_100g, *fec_policy);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}