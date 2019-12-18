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
struct nfp_rtsym_table {int /*<<< orphan*/  cpp; } ;
struct nfp_rtsym {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  nfp_err (int /*<<< orphan*/ ,char*,char const*,int) ; 
 struct nfp_rtsym* nfp_rtsym_lookup (struct nfp_rtsym_table*,char const*) ; 
 int nfp_rtsym_size (struct nfp_rtsym const*) ; 
 int nfp_rtsym_writel (int /*<<< orphan*/ ,struct nfp_rtsym const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfp_rtsym_writeq (int /*<<< orphan*/ ,struct nfp_rtsym const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nfp_rtsym_write_le(struct nfp_rtsym_table *rtbl, const char *name,
		       u64 value)
{
	const struct nfp_rtsym *sym;
	int err;

	sym = nfp_rtsym_lookup(rtbl, name);
	if (!sym)
		return -ENOENT;

	switch (nfp_rtsym_size(sym)) {
	case 4:
		err = nfp_rtsym_writel(rtbl->cpp, sym, 0, value);
		break;
	case 8:
		err = nfp_rtsym_writeq(rtbl->cpp, sym, 0, value);
		break;
	default:
		nfp_err(rtbl->cpp,
			"rtsym '%s': unsupported or non-scalar size: %lld\n",
			name, nfp_rtsym_size(sym));
		err = -EINVAL;
		break;
	}

	return err;
}