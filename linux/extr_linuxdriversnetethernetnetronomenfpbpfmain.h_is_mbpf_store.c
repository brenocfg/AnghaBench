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
struct TYPE_2__ {int code; } ;
struct nfp_insn_meta {TYPE_1__ insn; } ;

/* Variables and functions */
 int BPF_MEM ; 
 int BPF_SIZE_MASK ; 
 int BPF_STX ; 

__attribute__((used)) static inline bool is_mbpf_store(const struct nfp_insn_meta *meta)
{
	return (meta->insn.code & ~BPF_SIZE_MASK) == (BPF_STX | BPF_MEM);
}