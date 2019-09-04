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
typedef  scalar_t__ u8 ;
struct malidp_se_config {scalar_t__ hcoeff; scalar_t__ vcoeff; } ;
struct malidp_hw_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int MALIDP_SE_H_COEFFTAB ; 
 int MALIDP_SE_V_COEFFTAB ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dp500_se_scaling_coeffs ; 
 int /*<<< orphan*/  malidp500_se_write_pp_coefftab (struct malidp_hw_device*,int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int malidp500_se_set_scaling_coeffs(struct malidp_hw_device *hwdev,
					   struct malidp_se_config *se_config,
					   struct malidp_se_config *old_config)
{
	/* Get array indices into dp500_se_scaling_coeffs. */
	u8 h = (u8)se_config->hcoeff - 1;
	u8 v = (u8)se_config->vcoeff - 1;

	if (WARN_ON(h >= ARRAY_SIZE(dp500_se_scaling_coeffs) ||
		    v >= ARRAY_SIZE(dp500_se_scaling_coeffs)))
		return -EINVAL;

	if ((h == v) && (se_config->hcoeff != old_config->hcoeff ||
			 se_config->vcoeff != old_config->vcoeff)) {
		malidp500_se_write_pp_coefftab(hwdev,
					       (MALIDP_SE_V_COEFFTAB |
						MALIDP_SE_H_COEFFTAB),
					       0, v);
	} else {
		if (se_config->vcoeff != old_config->vcoeff)
			malidp500_se_write_pp_coefftab(hwdev,
						       MALIDP_SE_V_COEFFTAB,
						       0, v);
		if (se_config->hcoeff != old_config->hcoeff)
			malidp500_se_write_pp_coefftab(hwdev,
						       MALIDP_SE_H_COEFFTAB,
						       0, h);
	}

	return 0;
}