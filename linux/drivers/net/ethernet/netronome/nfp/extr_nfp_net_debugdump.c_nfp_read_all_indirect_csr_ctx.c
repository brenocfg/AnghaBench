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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  cpp_id; } ;
struct nfp_dumpspec_csr {TYPE_1__ cpp; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int NFP_IND_NUM_CONTEXTS ; 
 int nfp_read_indirect_csr (struct nfp_cpp*,int /*<<< orphan*/ ,int,int,int,void*) ; 

__attribute__((used)) static int
nfp_read_all_indirect_csr_ctx(struct nfp_cpp *cpp,
			      struct nfp_dumpspec_csr *spec_csr, u32 address,
			      u32 reg_sz, void *dest)
{
	u32 ctx;
	int err;

	for (ctx = 0; ctx < NFP_IND_NUM_CONTEXTS; ctx++) {
		err = nfp_read_indirect_csr(cpp, spec_csr->cpp.cpp_id, address,
					    reg_sz, ctx, dest + ctx * reg_sz);
		if (err)
			return err;
	}

	return 0;
}