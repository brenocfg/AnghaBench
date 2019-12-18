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
struct TYPE_2__ {scalar_t__ type; } ;
struct nfp_insn_meta {TYPE_1__ ptr; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ PTR_TO_PACKET ; 
 int mem_st_data (struct nfp_prog*,struct nfp_insn_meta*,unsigned int) ; 

__attribute__((used)) static int mem_st(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta,
		  unsigned int size)
{
	if (meta->ptr.type == PTR_TO_PACKET)
		return mem_st_data(nfp_prog, meta, size);

	return -EOPNOTSUPP;
}