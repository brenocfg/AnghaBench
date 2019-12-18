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
struct nfp_insn_meta {int dummy; } ;

/* Variables and functions */
 scalar_t__ BPF_JMP32 ; 
 scalar_t__ mbpf_class (struct nfp_insn_meta const*) ; 

__attribute__((used)) static inline bool is_mbpf_jmp32(const struct nfp_insn_meta *meta)
{
	return mbpf_class(meta) == BPF_JMP32;
}