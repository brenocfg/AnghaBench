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
struct ni_leakage_coeffients {int /*<<< orphan*/  t_ref; int /*<<< orphan*/  bv; int /*<<< orphan*/  av; int /*<<< orphan*/  t_intercept; int /*<<< orphan*/  t_slope; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int div64_s64 (int,int) ; 
 int /*<<< orphan*/  drm_fixp2int (int) ; 
 int drm_fixp_div (int,int) ; 
 int drm_fixp_exp (int) ; 
 int drm_fixp_mul (int,int) ; 
 int drm_int2fixp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void si_calculate_leakage_for_v_and_t_formula(const struct ni_leakage_coeffients *coeff,
						     u16 v, s32 t, u32 ileakage, u32 *leakage)
{
	s64 kt, kv, leakage_w, i_leakage, vddc;
	s64 temperature, t_slope, t_intercept, av, bv, t_ref;
	s64 tmp;

	i_leakage = div64_s64(drm_int2fixp(ileakage), 100);
	vddc = div64_s64(drm_int2fixp(v), 1000);
	temperature = div64_s64(drm_int2fixp(t), 1000);

	t_slope = div64_s64(drm_int2fixp(coeff->t_slope), 100000000);
	t_intercept = div64_s64(drm_int2fixp(coeff->t_intercept), 100000000);
	av = div64_s64(drm_int2fixp(coeff->av), 100000000);
	bv = div64_s64(drm_int2fixp(coeff->bv), 100000000);
	t_ref = drm_int2fixp(coeff->t_ref);

	tmp = drm_fixp_mul(t_slope, vddc) + t_intercept;
	kt = drm_fixp_exp(drm_fixp_mul(tmp, temperature));
	kt = drm_fixp_div(kt, drm_fixp_exp(drm_fixp_mul(tmp, t_ref)));
	kv = drm_fixp_mul(av, drm_fixp_exp(drm_fixp_mul(bv, vddc)));

	leakage_w = drm_fixp_mul(drm_fixp_mul(drm_fixp_mul(i_leakage, kt), kv), vddc);

	*leakage = drm_fixp2int(leakage_w * 1000);
}