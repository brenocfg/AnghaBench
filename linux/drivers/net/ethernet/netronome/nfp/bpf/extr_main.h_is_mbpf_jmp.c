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
 scalar_t__ is_mbpf_jmp32 (struct nfp_insn_meta const*) ; 
 scalar_t__ is_mbpf_jmp64 (struct nfp_insn_meta const*) ; 

__attribute__((used)) static inline bool is_mbpf_jmp(const struct nfp_insn_meta *meta)
{
	return is_mbpf_jmp32(meta) || is_mbpf_jmp64(meta);
}