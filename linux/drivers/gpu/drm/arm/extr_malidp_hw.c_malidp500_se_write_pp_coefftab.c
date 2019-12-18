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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct malidp_hw_device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int MALIDP500_SE_CONTROL ; 
 int MALIDP_SE_COEFFTAB_ADDR ; 
 int MALIDP_SE_COEFFTAB_ADDR_MASK ; 
 int MALIDP_SE_COEFFTAB_DATA ; 
 int MALIDP_SE_SCALING_CONTROL ; 
 int MALIDP_SE_SET_COEFFTAB_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** dp500_se_scaling_coeffs ; 
 int /*<<< orphan*/  malidp_hw_write (struct malidp_hw_device*,int,int) ; 

__attribute__((used)) static void malidp500_se_write_pp_coefftab(struct malidp_hw_device *hwdev,
					   u32 direction,
					   u16 addr,
					   u8 coeffs_id)
{
	int i;
	u16 scaling_control = MALIDP500_SE_CONTROL + MALIDP_SE_SCALING_CONTROL;

	malidp_hw_write(hwdev,
			direction | (addr & MALIDP_SE_COEFFTAB_ADDR_MASK),
			scaling_control + MALIDP_SE_COEFFTAB_ADDR);
	for (i = 0; i < ARRAY_SIZE(dp500_se_scaling_coeffs); ++i)
		malidp_hw_write(hwdev, MALIDP_SE_SET_COEFFTAB_DATA(
				dp500_se_scaling_coeffs[coeffs_id][i]),
				scaling_control + MALIDP_SE_COEFFTAB_DATA);
}