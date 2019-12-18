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
typedef  int u8 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int dummy; } ;
typedef  enum shf_sc { ____Placeholder_shf_sc } shf_sc ;

/* Variables and functions */
 int SHF_SC_NONE ; 
 int SHF_SC_R_SHF ; 
 int /*<<< orphan*/  emit_ld_field_any (struct nfp_prog*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
wrp_reg_subpart(struct nfp_prog *nfp_prog, swreg dst, swreg src, u8 field_len,
		u8 offset)
{
	enum shf_sc sc = offset ? SHF_SC_R_SHF : SHF_SC_NONE;
	u8 mask = (1 << field_len) - 1;

	emit_ld_field_any(nfp_prog, dst, mask, src, sc, offset * 8, true);
}