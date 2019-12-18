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
typedef  int u64 ;
struct nfp_rtsym_table {int dummy; } ;
struct nfp_rtsym {int dummy; } ;
struct nfp_dumpspec {int size; int /*<<< orphan*/  data; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_DUMP_SPEC_RTSYM ; 
 struct nfp_rtsym* nfp_rtsym_lookup (struct nfp_rtsym_table*,int /*<<< orphan*/ ) ; 
 int nfp_rtsym_read (struct nfp_cpp*,struct nfp_rtsym const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nfp_rtsym_size (struct nfp_rtsym const*) ; 
 int /*<<< orphan*/  nfp_warn (struct nfp_cpp*,char*) ; 
 int /*<<< orphan*/  vfree (struct nfp_dumpspec*) ; 
 struct nfp_dumpspec* vmalloc (int) ; 

struct nfp_dumpspec *
nfp_net_dump_load_dumpspec(struct nfp_cpp *cpp, struct nfp_rtsym_table *rtbl)
{
	const struct nfp_rtsym *specsym;
	struct nfp_dumpspec *dumpspec;
	int bytes_read;
	u64 sym_size;

	specsym = nfp_rtsym_lookup(rtbl, NFP_DUMP_SPEC_RTSYM);
	if (!specsym)
		return NULL;
	sym_size = nfp_rtsym_size(specsym);

	/* expected size of this buffer is in the order of tens of kilobytes */
	dumpspec = vmalloc(sizeof(*dumpspec) + sym_size);
	if (!dumpspec)
		return NULL;
	dumpspec->size = sym_size;

	bytes_read = nfp_rtsym_read(cpp, specsym, 0, dumpspec->data, sym_size);
	if (bytes_read != sym_size) {
		vfree(dumpspec);
		nfp_warn(cpp, "Debug dump specification read failed.\n");
		return NULL;
	}

	return dumpspec;
}