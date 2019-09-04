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
struct TYPE_2__ {scalar_t__ type; } ;
struct nfp_insn_meta {TYPE_1__ ptr; } ;

/* Variables and functions */
 scalar_t__ PTR_TO_PACKET ; 
 scalar_t__ is_mbpf_load (struct nfp_insn_meta const*) ; 

__attribute__((used)) static inline bool is_mbpf_load_pkt(const struct nfp_insn_meta *meta)
{
	return is_mbpf_load(meta) && meta->ptr.type == PTR_TO_PACKET;
}