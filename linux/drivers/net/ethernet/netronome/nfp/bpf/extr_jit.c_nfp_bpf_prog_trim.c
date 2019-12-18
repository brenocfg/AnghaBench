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
typedef  int /*<<< orphan*/  u64 ;
struct nfp_prog {int prog_len; int __prog_alloc_len; void* prog; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static void nfp_bpf_prog_trim(struct nfp_prog *nfp_prog)
{
	void *prog;

	prog = kvmalloc_array(nfp_prog->prog_len, sizeof(u64), GFP_KERNEL);
	if (!prog)
		return;

	nfp_prog->__prog_alloc_len = nfp_prog->prog_len * sizeof(u64);
	memcpy(prog, nfp_prog->prog, nfp_prog->__prog_alloc_len);
	kvfree(nfp_prog->prog);
	nfp_prog->prog = prog;
}