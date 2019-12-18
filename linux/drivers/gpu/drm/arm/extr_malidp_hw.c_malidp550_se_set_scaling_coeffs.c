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
struct malidp_se_config {int /*<<< orphan*/  hcoeff; int /*<<< orphan*/  vcoeff; } ;
struct malidp_hw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MALIDP550_SE_CONTROL ; 
 int MALIDP550_SE_CTL_HCSEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MALIDP550_SE_CTL_SEL_MASK ; 
 int MALIDP550_SE_CTL_VCSEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malidp_hw_clearbits (struct malidp_hw_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malidp_hw_setbits (struct malidp_hw_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int malidp550_se_set_scaling_coeffs(struct malidp_hw_device *hwdev,
					   struct malidp_se_config *se_config,
					   struct malidp_se_config *old_config)
{
	u32 mask = MALIDP550_SE_CTL_VCSEL(MALIDP550_SE_CTL_SEL_MASK) |
		   MALIDP550_SE_CTL_HCSEL(MALIDP550_SE_CTL_SEL_MASK);
	u32 new_value = MALIDP550_SE_CTL_VCSEL(se_config->vcoeff) |
			MALIDP550_SE_CTL_HCSEL(se_config->hcoeff);

	malidp_hw_clearbits(hwdev, mask, MALIDP550_SE_CONTROL);
	malidp_hw_setbits(hwdev, new_value, MALIDP550_SE_CONTROL);
	return 0;
}