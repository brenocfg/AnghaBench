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
typedef  int /*<<< orphan*/  u32 ;
struct nfp_rtsym_table {int dummy; } ;
struct nfp_rtsym {int size; int /*<<< orphan*/  addr; int /*<<< orphan*/  domain; int /*<<< orphan*/  target; } ;
struct nfp_dumpspec {int size; int /*<<< orphan*/  data; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_CPP_ACTION_RW ; 
 int /*<<< orphan*/  NFP_CPP_ISLAND_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFP_DUMP_SPEC_RTSYM ; 
 int nfp_cpp_read (struct nfp_cpp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct nfp_rtsym* nfp_rtsym_lookup (struct nfp_rtsym_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_warn (struct nfp_cpp*,char*) ; 
 int /*<<< orphan*/  vfree (struct nfp_dumpspec*) ; 
 struct nfp_dumpspec* vmalloc (int) ; 

struct nfp_dumpspec *
nfp_net_dump_load_dumpspec(struct nfp_cpp *cpp, struct nfp_rtsym_table *rtbl)
{
	const struct nfp_rtsym *specsym;
	struct nfp_dumpspec *dumpspec;
	int bytes_read;
	u32 cpp_id;

	specsym = nfp_rtsym_lookup(rtbl, NFP_DUMP_SPEC_RTSYM);
	if (!specsym)
		return NULL;

	/* expected size of this buffer is in the order of tens of kilobytes */
	dumpspec = vmalloc(sizeof(*dumpspec) + specsym->size);
	if (!dumpspec)
		return NULL;

	dumpspec->size = specsym->size;

	cpp_id = NFP_CPP_ISLAND_ID(specsym->target, NFP_CPP_ACTION_RW, 0,
				   specsym->domain);

	bytes_read = nfp_cpp_read(cpp, cpp_id, specsym->addr, dumpspec->data,
				  specsym->size);
	if (bytes_read != specsym->size) {
		vfree(dumpspec);
		nfp_warn(cpp, "Debug dump specification read failed.\n");
		return NULL;
	}

	return dumpspec;
}