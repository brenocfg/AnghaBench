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
typedef  scalar_t__ u32 ;
struct nfp_dump_tl {void* length; void* type; } ;
struct nfp_dump_state {scalar_t__ buf_size; scalar_t__ dumped_size; struct nfp_dump_tl* p; } ;

/* Variables and functions */
 int ENOSPC ; 
 void* cpu_to_be32 (scalar_t__) ; 

__attribute__((used)) static int nfp_add_tlv(u32 type, u32 total_tlv_sz, struct nfp_dump_state *dump)
{
	struct nfp_dump_tl *tl = dump->p;

	if (total_tlv_sz > dump->buf_size)
		return -ENOSPC;

	if (dump->buf_size - total_tlv_sz < dump->dumped_size)
		return -ENOSPC;

	tl->type = cpu_to_be32(type);
	tl->length = cpu_to_be32(total_tlv_sz - sizeof(*tl));

	dump->dumped_size += total_tlv_sz;
	dump->p += total_tlv_sz;

	return 0;
}