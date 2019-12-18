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
 int ENOENT ; 
 int /*<<< orphan*/  NFP_HWINFO_LOOKUP_SIZE ; 
 int __nfp_nsp_hwinfo_lookup (struct nfp_nsp*,void*,unsigned int,int) ; 
 unsigned int min_t (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nfp_nsp_has_hwinfo_lookup (struct nfp_nsp*) ; 
 int /*<<< orphan*/  strcpy (void*,char const*) ; 
 unsigned int strnlen (void*,unsigned int) ; 
 int /*<<< orphan*/  u32 ; 

int nfp_nsp_hwinfo_lookup_optional(struct nfp_nsp *state, void *buf,
				   unsigned int size, const char *default_val)
{
	int err;

	/* Ensure that the default value is usable irrespective of whether
	 * it is actually going to be used.
	 */
	if (strnlen(default_val, size) == size)
		return -EINVAL;

	if (!nfp_nsp_has_hwinfo_lookup(state)) {
		strcpy(buf, default_val);
		return 0;
	}

	size = min_t(u32, size, NFP_HWINFO_LOOKUP_SIZE);

	err = __nfp_nsp_hwinfo_lookup(state, buf, size, true);
	if (err) {
		if (err == -ENOENT) {
			strcpy(buf, default_val);
			return 0;
		}

		nfp_err(state->cpp, "NSP HWinfo lookup failed: %d\n", err);
		return err;
	}

	if (strnlen(buf, size) == size) {
		nfp_err(state->cpp, "NSP HWinfo value not NULL-terminated\n");
		return -EINVAL;
	}

	return 0;
}