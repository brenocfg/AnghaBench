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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct nfp_insn_meta {TYPE_1__ insn; } ;

/* Variables and functions */
 scalar_t__ BPF_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_MEM ; 
 scalar_t__ BPF_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_ST ; 

__attribute__((used)) static inline bool is_mbpf_classic_store(const struct nfp_insn_meta *meta)
{
	u8 code = meta->insn.code;

	return BPF_CLASS(code) == BPF_ST && BPF_MODE(code) == BPF_MEM;
}