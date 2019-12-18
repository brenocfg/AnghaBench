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
struct nfp_rtsym {int dummy; } ;
struct nfp_pf {int /*<<< orphan*/  cpp; int /*<<< orphan*/  rtbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 struct nfp_rtsym const* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_err (int /*<<< orphan*/ ,char*,char const*,...) ; 
 struct nfp_rtsym* nfp_rtsym_lookup (int /*<<< orphan*/ ,char const*) ; 
 unsigned int nfp_rtsym_size (struct nfp_rtsym const*) ; 

__attribute__((used)) static const struct nfp_rtsym *
nfp_abm_ctrl_find_rtsym(struct nfp_pf *pf, const char *name, unsigned int size)
{
	const struct nfp_rtsym *sym;

	sym = nfp_rtsym_lookup(pf->rtbl, name);
	if (!sym) {
		nfp_err(pf->cpp, "Symbol '%s' not found\n", name);
		return ERR_PTR(-ENOENT);
	}
	if (nfp_rtsym_size(sym) != size) {
		nfp_err(pf->cpp,
			"Symbol '%s' wrong size: expected %u got %llu\n",
			name, size, nfp_rtsym_size(sym));
		return ERR_PTR(-EINVAL);
	}

	return sym;
}