#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nfp_prog {scalar_t__ type; } ;
struct TYPE_5__ {scalar_t__ value; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_2__ var_off; scalar_t__ off; } ;
struct TYPE_4__ {scalar_t__ do_init; scalar_t__ range_end; } ;
struct nfp_insn_meta {TYPE_3__ ptr; TYPE_1__ pkt_cache; scalar_t__ ldst_gather_len; } ;

/* Variables and functions */
 scalar_t__ BPF_PROG_TYPE_XDP ; 
 int EOPNOTSUPP ; 
 scalar_t__ PTR_TO_CTX ; 
 scalar_t__ PTR_TO_MAP_VALUE ; 
 scalar_t__ PTR_TO_PACKET ; 
 scalar_t__ PTR_TO_STACK ; 
 int mem_ldx_data (struct nfp_prog*,struct nfp_insn_meta*,unsigned int) ; 
 int mem_ldx_data_from_pktcache (struct nfp_prog*,struct nfp_insn_meta*,unsigned int) ; 
 int /*<<< orphan*/  mem_ldx_data_init_pktcache (struct nfp_prog*,struct nfp_insn_meta*) ; 
 int mem_ldx_emem (struct nfp_prog*,struct nfp_insn_meta*,unsigned int) ; 
 int mem_ldx_skb (struct nfp_prog*,struct nfp_insn_meta*,unsigned int) ; 
 int mem_ldx_stack (struct nfp_prog*,struct nfp_insn_meta*,unsigned int,scalar_t__) ; 
 int mem_ldx_xdp (struct nfp_prog*,struct nfp_insn_meta*,unsigned int) ; 
 int nfp_cpp_memcpy (struct nfp_prog*,struct nfp_insn_meta*) ; 

__attribute__((used)) static int
mem_ldx(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta,
	unsigned int size)
{
	if (meta->ldst_gather_len)
		return nfp_cpp_memcpy(nfp_prog, meta);

	if (meta->ptr.type == PTR_TO_CTX) {
		if (nfp_prog->type == BPF_PROG_TYPE_XDP)
			return mem_ldx_xdp(nfp_prog, meta, size);
		else
			return mem_ldx_skb(nfp_prog, meta, size);
	}

	if (meta->ptr.type == PTR_TO_PACKET) {
		if (meta->pkt_cache.range_end) {
			if (meta->pkt_cache.do_init)
				mem_ldx_data_init_pktcache(nfp_prog, meta);

			return mem_ldx_data_from_pktcache(nfp_prog, meta, size);
		} else {
			return mem_ldx_data(nfp_prog, meta, size);
		}
	}

	if (meta->ptr.type == PTR_TO_STACK)
		return mem_ldx_stack(nfp_prog, meta, size,
				     meta->ptr.off + meta->ptr.var_off.value);

	if (meta->ptr.type == PTR_TO_MAP_VALUE)
		return mem_ldx_emem(nfp_prog, meta, size);

	return -EOPNOTSUPP;
}