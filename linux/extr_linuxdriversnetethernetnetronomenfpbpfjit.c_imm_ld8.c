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
struct nfp_prog {int dummy; } ;
struct nfp_insn_meta {int /*<<< orphan*/  double_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  imm_ld8_part2 ; 

__attribute__((used)) static int imm_ld8(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	meta->double_cb = imm_ld8_part2;
	return 0;
}