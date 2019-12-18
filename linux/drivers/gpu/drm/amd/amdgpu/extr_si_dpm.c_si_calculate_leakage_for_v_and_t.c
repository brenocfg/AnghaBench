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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ni_leakage_coeffients {int dummy; } ;
struct amdgpu_device {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  si_calculate_leakage_for_v_and_t_formula (struct ni_leakage_coeffients const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void si_calculate_leakage_for_v_and_t(struct amdgpu_device *adev,
					     const struct ni_leakage_coeffients *coeff,
					     u16 v,
					     s32 t,
					     u32 i_leakage,
					     u32 *leakage)
{
	si_calculate_leakage_for_v_and_t_formula(coeff, v, t, i_leakage, leakage);
}