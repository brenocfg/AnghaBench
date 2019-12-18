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
 int /*<<< orphan*/  fec_override_cap_100g ; 
 int /*<<< orphan*/  fec_override_cap_10g_40g ; 
 int /*<<< orphan*/  fec_override_cap_25g ; 
 int /*<<< orphan*/  fec_override_cap_50g ; 
 int /*<<< orphan*/  fec_override_cap_56g ; 
 int /*<<< orphan*/  pplm_reg ; 

__attribute__((used)) static int mlx5e_get_fec_cap_field(u32 *pplm,
				   u8 *fec_cap,
				   u32 speed)
{
	switch (speed) {
	case 10000:
	case 40000:
		*fec_cap = MLX5_GET(pplm_reg, pplm,
				    fec_override_cap_10g_40g);
		break;
	case 25000:
		*fec_cap = MLX5_GET(pplm_reg, pplm,
				    fec_override_cap_25g);
		break;
	case 50000:
		*fec_cap = MLX5_GET(pplm_reg, pplm,
				    fec_override_cap_50g);
		break;
	case 56000:
		*fec_cap = MLX5_GET(pplm_reg, pplm,
				    fec_override_cap_56g);
		break;
	case 100000:
		*fec_cap = MLX5_GET(pplm_reg, pplm,
				    fec_override_cap_100g);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}