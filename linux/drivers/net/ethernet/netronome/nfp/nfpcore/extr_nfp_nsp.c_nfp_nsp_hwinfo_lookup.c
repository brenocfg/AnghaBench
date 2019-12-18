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
struct nfp_nsp {int /*<<< orphan*/  cpp; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NFP_HWINFO_LOOKUP_SIZE ; 
 int __nfp_nsp_hwinfo_lookup (struct nfp_nsp*,void*,unsigned int,int) ; 
 unsigned int min_t (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int strnlen (void*,unsigned int) ; 
 int /*<<< orphan*/  u32 ; 

int nfp_nsp_hwinfo_lookup(struct nfp_nsp *state, void *buf, unsigned int size)
{
	int err;

	size = min_t(u32, size, NFP_HWINFO_LOOKUP_SIZE);

	err = __nfp_nsp_hwinfo_lookup(state, buf, size, false);
	if (err)
		return err;

	if (strnlen(buf, size) == size) {
		nfp_err(state->cpp, "NSP HWinfo value not NULL-terminated\n");
		return -EINVAL;
	}

	return 0;
}