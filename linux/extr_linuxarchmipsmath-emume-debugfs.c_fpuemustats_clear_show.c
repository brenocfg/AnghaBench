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
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  trunc_l_d; int /*<<< orphan*/  trunc_l_s; int /*<<< orphan*/  trunc_w_d; int /*<<< orphan*/  trunc_w_s; int /*<<< orphan*/  sub_d; int /*<<< orphan*/  sub_s; int /*<<< orphan*/  sqrt_d; int /*<<< orphan*/  sqrt_s; int /*<<< orphan*/  selnez_d; int /*<<< orphan*/  selnez_s; int /*<<< orphan*/  seleqz_d; int /*<<< orphan*/  seleqz_s; int /*<<< orphan*/  sel_d; int /*<<< orphan*/  sel_s; int /*<<< orphan*/  rsqrt_d; int /*<<< orphan*/  rsqrt_s; int /*<<< orphan*/  round_l_d; int /*<<< orphan*/  round_l_s; int /*<<< orphan*/  round_w_d; int /*<<< orphan*/  round_w_s; int /*<<< orphan*/  rint_d; int /*<<< orphan*/  rint_s; int /*<<< orphan*/  recip_d; int /*<<< orphan*/  recip_s; int /*<<< orphan*/  neg_d; int /*<<< orphan*/  neg_s; int /*<<< orphan*/  mul_d; int /*<<< orphan*/  mul_s; int /*<<< orphan*/  msubf_d; int /*<<< orphan*/  msubf_s; int /*<<< orphan*/  mov_d; int /*<<< orphan*/  mov_s; int /*<<< orphan*/  mina_d; int /*<<< orphan*/  mina_s; int /*<<< orphan*/  min_d; int /*<<< orphan*/  min_s; int /*<<< orphan*/  maxa_d; int /*<<< orphan*/  maxa_s; int /*<<< orphan*/  max_d; int /*<<< orphan*/  max_s; int /*<<< orphan*/  maddf_d; int /*<<< orphan*/  maddf_s; int /*<<< orphan*/  floor_l_d; int /*<<< orphan*/  floor_l_s; int /*<<< orphan*/  floor_w_d; int /*<<< orphan*/  floor_w_s; int /*<<< orphan*/  div_d; int /*<<< orphan*/  div_s; int /*<<< orphan*/  cvt_w_d; int /*<<< orphan*/  cvt_w_s; int /*<<< orphan*/  cvt_s_w; int /*<<< orphan*/  cvt_s_l; int /*<<< orphan*/  cvt_s_d; int /*<<< orphan*/  cvt_l_d; int /*<<< orphan*/  cvt_l_s; int /*<<< orphan*/  cvt_d_w; int /*<<< orphan*/  cvt_d_s; int /*<<< orphan*/  cvt_d_l; int /*<<< orphan*/  cmp_sune_d; int /*<<< orphan*/  cmp_sune_s; int /*<<< orphan*/  cmp_sun_d; int /*<<< orphan*/  cmp_sun_s; int /*<<< orphan*/  cmp_sult_d; int /*<<< orphan*/  cmp_sult_s; int /*<<< orphan*/  cmp_sule_d; int /*<<< orphan*/  cmp_sule_s; int /*<<< orphan*/  cmp_sueq_d; int /*<<< orphan*/  cmp_sueq_s; int /*<<< orphan*/  cmp_sor_d; int /*<<< orphan*/  cmp_sor_s; int /*<<< orphan*/  cmp_sne_d; int /*<<< orphan*/  cmp_sne_s; int /*<<< orphan*/  cmp_slt_d; int /*<<< orphan*/  cmp_slt_s; int /*<<< orphan*/  cmp_sle_d; int /*<<< orphan*/  cmp_sle_s; int /*<<< orphan*/  cmp_seq_d; int /*<<< orphan*/  cmp_seq_s; int /*<<< orphan*/  cmp_saf_d; int /*<<< orphan*/  cmp_saf_s; int /*<<< orphan*/  cmp_une_d; int /*<<< orphan*/  cmp_une_s; int /*<<< orphan*/  cmp_un_d; int /*<<< orphan*/  cmp_un_s; int /*<<< orphan*/  cmp_ult_d; int /*<<< orphan*/  cmp_ult_s; int /*<<< orphan*/  cmp_ule_d; int /*<<< orphan*/  cmp_ule_s; int /*<<< orphan*/  cmp_ueq_d; int /*<<< orphan*/  cmp_ueq_s; int /*<<< orphan*/  cmp_or_d; int /*<<< orphan*/  cmp_or_s; int /*<<< orphan*/  cmp_ne_d; int /*<<< orphan*/  cmp_ne_s; int /*<<< orphan*/  cmp_lt_d; int /*<<< orphan*/  cmp_lt_s; int /*<<< orphan*/  cmp_le_d; int /*<<< orphan*/  cmp_le_s; int /*<<< orphan*/  cmp_eq_d; int /*<<< orphan*/  cmp_eq_s; int /*<<< orphan*/  cmp_af_d; int /*<<< orphan*/  cmp_af_s; int /*<<< orphan*/  class_d; int /*<<< orphan*/  class_s; int /*<<< orphan*/  ceil_l_d; int /*<<< orphan*/  ceil_l_s; int /*<<< orphan*/  ceil_w_d; int /*<<< orphan*/  ceil_w_s; int /*<<< orphan*/  bc1nez; int /*<<< orphan*/  bc1eqz; int /*<<< orphan*/  add_d; int /*<<< orphan*/  add_s; int /*<<< orphan*/  abs_d; int /*<<< orphan*/  abs_s; int /*<<< orphan*/  ds_emul; int /*<<< orphan*/  ieee754_invalidop; int /*<<< orphan*/  ieee754_zerodiv; int /*<<< orphan*/  ieee754_overflow; int /*<<< orphan*/  ieee754_underflow; int /*<<< orphan*/  ieee754_inexact; int /*<<< orphan*/  errors; int /*<<< orphan*/  cp1xops; int /*<<< orphan*/  cp1ops; int /*<<< orphan*/  branches; int /*<<< orphan*/  stores; int /*<<< orphan*/  loads; int /*<<< orphan*/  emulated; } ;

/* Variables and functions */
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ fpuemustats ; 

__attribute__((used)) static int fpuemustats_clear_show(struct seq_file *s, void *unused)
{
	__this_cpu_write((fpuemustats).emulated, 0);
	__this_cpu_write((fpuemustats).loads, 0);
	__this_cpu_write((fpuemustats).stores, 0);
	__this_cpu_write((fpuemustats).branches, 0);
	__this_cpu_write((fpuemustats).cp1ops, 0);
	__this_cpu_write((fpuemustats).cp1xops, 0);
	__this_cpu_write((fpuemustats).errors, 0);
	__this_cpu_write((fpuemustats).ieee754_inexact, 0);
	__this_cpu_write((fpuemustats).ieee754_underflow, 0);
	__this_cpu_write((fpuemustats).ieee754_overflow, 0);
	__this_cpu_write((fpuemustats).ieee754_zerodiv, 0);
	__this_cpu_write((fpuemustats).ieee754_invalidop, 0);
	__this_cpu_write((fpuemustats).ds_emul, 0);

	__this_cpu_write((fpuemustats).abs_s, 0);
	__this_cpu_write((fpuemustats).abs_d, 0);
	__this_cpu_write((fpuemustats).add_s, 0);
	__this_cpu_write((fpuemustats).add_d, 0);
	__this_cpu_write((fpuemustats).bc1eqz, 0);
	__this_cpu_write((fpuemustats).bc1nez, 0);
	__this_cpu_write((fpuemustats).ceil_w_s, 0);
	__this_cpu_write((fpuemustats).ceil_w_d, 0);
	__this_cpu_write((fpuemustats).ceil_l_s, 0);
	__this_cpu_write((fpuemustats).ceil_l_d, 0);
	__this_cpu_write((fpuemustats).class_s, 0);
	__this_cpu_write((fpuemustats).class_d, 0);
	__this_cpu_write((fpuemustats).cmp_af_s, 0);
	__this_cpu_write((fpuemustats).cmp_af_d, 0);
	__this_cpu_write((fpuemustats).cmp_eq_s, 0);
	__this_cpu_write((fpuemustats).cmp_eq_d, 0);
	__this_cpu_write((fpuemustats).cmp_le_s, 0);
	__this_cpu_write((fpuemustats).cmp_le_d, 0);
	__this_cpu_write((fpuemustats).cmp_lt_s, 0);
	__this_cpu_write((fpuemustats).cmp_lt_d, 0);
	__this_cpu_write((fpuemustats).cmp_ne_s, 0);
	__this_cpu_write((fpuemustats).cmp_ne_d, 0);
	__this_cpu_write((fpuemustats).cmp_or_s, 0);
	__this_cpu_write((fpuemustats).cmp_or_d, 0);
	__this_cpu_write((fpuemustats).cmp_ueq_s, 0);
	__this_cpu_write((fpuemustats).cmp_ueq_d, 0);
	__this_cpu_write((fpuemustats).cmp_ule_s, 0);
	__this_cpu_write((fpuemustats).cmp_ule_d, 0);
	__this_cpu_write((fpuemustats).cmp_ult_s, 0);
	__this_cpu_write((fpuemustats).cmp_ult_d, 0);
	__this_cpu_write((fpuemustats).cmp_un_s, 0);
	__this_cpu_write((fpuemustats).cmp_un_d, 0);
	__this_cpu_write((fpuemustats).cmp_une_s, 0);
	__this_cpu_write((fpuemustats).cmp_une_d, 0);
	__this_cpu_write((fpuemustats).cmp_saf_s, 0);
	__this_cpu_write((fpuemustats).cmp_saf_d, 0);
	__this_cpu_write((fpuemustats).cmp_seq_s, 0);
	__this_cpu_write((fpuemustats).cmp_seq_d, 0);
	__this_cpu_write((fpuemustats).cmp_sle_s, 0);
	__this_cpu_write((fpuemustats).cmp_sle_d, 0);
	__this_cpu_write((fpuemustats).cmp_slt_s, 0);
	__this_cpu_write((fpuemustats).cmp_slt_d, 0);
	__this_cpu_write((fpuemustats).cmp_sne_s, 0);
	__this_cpu_write((fpuemustats).cmp_sne_d, 0);
	__this_cpu_write((fpuemustats).cmp_sor_s, 0);
	__this_cpu_write((fpuemustats).cmp_sor_d, 0);
	__this_cpu_write((fpuemustats).cmp_sueq_s, 0);
	__this_cpu_write((fpuemustats).cmp_sueq_d, 0);
	__this_cpu_write((fpuemustats).cmp_sule_s, 0);
	__this_cpu_write((fpuemustats).cmp_sule_d, 0);
	__this_cpu_write((fpuemustats).cmp_sult_s, 0);
	__this_cpu_write((fpuemustats).cmp_sult_d, 0);
	__this_cpu_write((fpuemustats).cmp_sun_s, 0);
	__this_cpu_write((fpuemustats).cmp_sun_d, 0);
	__this_cpu_write((fpuemustats).cmp_sune_s, 0);
	__this_cpu_write((fpuemustats).cmp_sune_d, 0);
	__this_cpu_write((fpuemustats).cvt_d_l, 0);
	__this_cpu_write((fpuemustats).cvt_d_s, 0);
	__this_cpu_write((fpuemustats).cvt_d_w, 0);
	__this_cpu_write((fpuemustats).cvt_l_s, 0);
	__this_cpu_write((fpuemustats).cvt_l_d, 0);
	__this_cpu_write((fpuemustats).cvt_s_d, 0);
	__this_cpu_write((fpuemustats).cvt_s_l, 0);
	__this_cpu_write((fpuemustats).cvt_s_w, 0);
	__this_cpu_write((fpuemustats).cvt_w_s, 0);
	__this_cpu_write((fpuemustats).cvt_w_d, 0);
	__this_cpu_write((fpuemustats).div_s, 0);
	__this_cpu_write((fpuemustats).div_d, 0);
	__this_cpu_write((fpuemustats).floor_w_s, 0);
	__this_cpu_write((fpuemustats).floor_w_d, 0);
	__this_cpu_write((fpuemustats).floor_l_s, 0);
	__this_cpu_write((fpuemustats).floor_l_d, 0);
	__this_cpu_write((fpuemustats).maddf_s, 0);
	__this_cpu_write((fpuemustats).maddf_d, 0);
	__this_cpu_write((fpuemustats).max_s, 0);
	__this_cpu_write((fpuemustats).max_d, 0);
	__this_cpu_write((fpuemustats).maxa_s, 0);
	__this_cpu_write((fpuemustats).maxa_d, 0);
	__this_cpu_write((fpuemustats).min_s, 0);
	__this_cpu_write((fpuemustats).min_d, 0);
	__this_cpu_write((fpuemustats).mina_s, 0);
	__this_cpu_write((fpuemustats).mina_d, 0);
	__this_cpu_write((fpuemustats).mov_s, 0);
	__this_cpu_write((fpuemustats).mov_d, 0);
	__this_cpu_write((fpuemustats).msubf_s, 0);
	__this_cpu_write((fpuemustats).msubf_d, 0);
	__this_cpu_write((fpuemustats).mul_s, 0);
	__this_cpu_write((fpuemustats).mul_d, 0);
	__this_cpu_write((fpuemustats).neg_s, 0);
	__this_cpu_write((fpuemustats).neg_d, 0);
	__this_cpu_write((fpuemustats).recip_s, 0);
	__this_cpu_write((fpuemustats).recip_d, 0);
	__this_cpu_write((fpuemustats).rint_s, 0);
	__this_cpu_write((fpuemustats).rint_d, 0);
	__this_cpu_write((fpuemustats).round_w_s, 0);
	__this_cpu_write((fpuemustats).round_w_d, 0);
	__this_cpu_write((fpuemustats).round_l_s, 0);
	__this_cpu_write((fpuemustats).round_l_d, 0);
	__this_cpu_write((fpuemustats).rsqrt_s, 0);
	__this_cpu_write((fpuemustats).rsqrt_d, 0);
	__this_cpu_write((fpuemustats).sel_s, 0);
	__this_cpu_write((fpuemustats).sel_d, 0);
	__this_cpu_write((fpuemustats).seleqz_s, 0);
	__this_cpu_write((fpuemustats).seleqz_d, 0);
	__this_cpu_write((fpuemustats).selnez_s, 0);
	__this_cpu_write((fpuemustats).selnez_d, 0);
	__this_cpu_write((fpuemustats).sqrt_s, 0);
	__this_cpu_write((fpuemustats).sqrt_d, 0);
	__this_cpu_write((fpuemustats).sub_s, 0);
	__this_cpu_write((fpuemustats).sub_d, 0);
	__this_cpu_write((fpuemustats).trunc_w_s, 0);
	__this_cpu_write((fpuemustats).trunc_w_d, 0);
	__this_cpu_write((fpuemustats).trunc_l_s, 0);
	__this_cpu_write((fpuemustats).trunc_l_d, 0);

	return 0;
}