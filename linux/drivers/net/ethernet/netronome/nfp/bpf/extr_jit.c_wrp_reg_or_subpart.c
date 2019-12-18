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
 int SHF_SC_L_SHF ; 
 int SHF_SC_NONE ; 
 int /*<<< orphan*/  emit_ld_field (struct nfp_prog*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
wrp_reg_or_subpart(struct nfp_prog *nfp_prog, swreg dst, swreg src,
		   u8 field_len, u8 offset)
{
	enum shf_sc sc = offset ? SHF_SC_L_SHF : SHF_SC_NONE;
	u8 mask = ((1 << field_len) - 1) << offset;

	emit_ld_field(nfp_prog, dst, mask, src, sc, 32 - offset * 8);
}