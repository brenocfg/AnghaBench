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
typedef  int /*<<< orphan*/  u32 ;
struct nfp_rtsym_table {int /*<<< orphan*/  cpp; } ;
struct nfp_rtsym {int size; int /*<<< orphan*/  addr; int /*<<< orphan*/  domain; int /*<<< orphan*/  target; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  NFP_CPP_ACTION_RW ; 
 int /*<<< orphan*/  NFP_CPP_ISLAND_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfp_cpp_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfp_cpp_writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_err (int /*<<< orphan*/ ,char*,char const*,int) ; 
 struct nfp_rtsym* nfp_rtsym_lookup (struct nfp_rtsym_table*,char const*) ; 

int nfp_rtsym_write_le(struct nfp_rtsym_table *rtbl, const char *name,
		       u64 value)
{
	const struct nfp_rtsym *sym;
	int err;
	u32 id;

	sym = nfp_rtsym_lookup(rtbl, name);
	if (!sym)
		return -ENOENT;

	id = NFP_CPP_ISLAND_ID(sym->target, NFP_CPP_ACTION_RW, 0, sym->domain);

	switch (sym->size) {
	case 4:
		err = nfp_cpp_writel(rtbl->cpp, id, sym->addr, value);
		break;
	case 8:
		err = nfp_cpp_writeq(rtbl->cpp, id, sym->addr, value);
		break;
	default:
		nfp_err(rtbl->cpp,
			"rtsym '%s' unsupported or non-scalar size: %lld\n",
			name, sym->size);
		err = -EINVAL;
		break;
	}

	return err;
}