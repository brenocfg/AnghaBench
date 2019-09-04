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
struct nfp_prog {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  off; } ;
struct nfp_insn_meta {TYPE_1__ insn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BR_UNC ; 
 int /*<<< orphan*/  emit_br (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jump(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	emit_br(nfp_prog, BR_UNC, meta->insn.off, 0);

	return 0;
}