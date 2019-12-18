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
typedef  unsigned long long u64 ;
typedef  unsigned long long u32 ;
struct nfp_rtsym_table {int /*<<< orphan*/  cpp; } ;
struct nfp_rtsym {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  nfp_err (int /*<<< orphan*/ ,char*,char const*,int) ; 
 struct nfp_rtsym* nfp_rtsym_lookup (struct nfp_rtsym_table*,char const*) ; 
 int nfp_rtsym_readl (int /*<<< orphan*/ ,struct nfp_rtsym const*,int /*<<< orphan*/ ,unsigned long long*) ; 
 int nfp_rtsym_readq (int /*<<< orphan*/ ,struct nfp_rtsym const*,int /*<<< orphan*/ ,unsigned long long*) ; 
 int nfp_rtsym_size (struct nfp_rtsym const*) ; 

u64 nfp_rtsym_read_le(struct nfp_rtsym_table *rtbl, const char *name,
		      int *error)
{
	const struct nfp_rtsym *sym;
	u32 val32;
	u64 val;
	int err;

	sym = nfp_rtsym_lookup(rtbl, name);
	if (!sym) {
		err = -ENOENT;
		goto exit;
	}

	switch (nfp_rtsym_size(sym)) {
	case 4:
		err = nfp_rtsym_readl(rtbl->cpp, sym, 0, &val32);
		val = val32;
		break;
	case 8:
		err = nfp_rtsym_readq(rtbl->cpp, sym, 0, &val);
		break;
	default:
		nfp_err(rtbl->cpp,
			"rtsym '%s': unsupported or non-scalar size: %lld\n",
			name, nfp_rtsym_size(sym));
		err = -EINVAL;
		break;
	}

exit:
	if (error)
		*error = err;

	if (err)
		return ~0ULL;
	return val;
}