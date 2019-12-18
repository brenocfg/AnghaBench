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
struct nfp_prog {int dummy; } ;
struct nfp_insn_meta {int flags; } ;

/* Variables and functions */
 int FLAG_INSN_DO_ZEXT ; 
 int /*<<< orphan*/  reg_both (scalar_t__) ; 
 int /*<<< orphan*/  wrp_immed (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wrp_zext(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta, u8 dst)
{
	if (meta->flags & FLAG_INSN_DO_ZEXT)
		wrp_immed(nfp_prog, reg_both(dst + 1), 0);
}