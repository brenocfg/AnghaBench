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
typedef  scalar_t__ u32 ;
typedef  enum malidp_scaling_coeff_set { ____Placeholder_malidp_scaling_coeff_set } malidp_scaling_coeff_set ;

/* Variables and functions */
 scalar_t__ FP_0_36363 ; 
 scalar_t__ FP_0_50000 ; 
 scalar_t__ FP_0_66667 ; 
 scalar_t__ FP_1_00000 ; 
 int MALIDP_DOWNSCALING_1_5_COEFFS ; 
 int MALIDP_DOWNSCALING_2_75_COEFFS ; 
 int MALIDP_DOWNSCALING_2_COEFFS ; 
 int MALIDP_DOWNSCALING_4_COEFFS ; 
 int MALIDP_UPSCALING_COEFFS ; 

__attribute__((used)) static inline enum malidp_scaling_coeff_set
malidp_se_select_coeffs(u32 upscale_factor)
{
	return (upscale_factor >= FP_1_00000) ? MALIDP_UPSCALING_COEFFS :
	       (upscale_factor >= FP_0_66667) ? MALIDP_DOWNSCALING_1_5_COEFFS :
	       (upscale_factor >= FP_0_50000) ? MALIDP_DOWNSCALING_2_COEFFS :
	       (upscale_factor >= FP_0_36363) ? MALIDP_DOWNSCALING_2_75_COEFFS :
	       MALIDP_DOWNSCALING_4_COEFFS;
}