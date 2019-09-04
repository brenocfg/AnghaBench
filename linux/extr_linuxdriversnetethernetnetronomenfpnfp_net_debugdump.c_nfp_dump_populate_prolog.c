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
struct nfp_dump_state {int /*<<< orphan*/  requested_level; struct nfp_dump_prolog* p; } ;
struct nfp_dump_prolog {int /*<<< orphan*/  dump_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN8 (int) ; 
 int /*<<< orphan*/  NFP_DUMPSPEC_TYPE_PROLOG ; 
 int nfp_add_tlv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfp_dump_state*) ; 

__attribute__((used)) static int nfp_dump_populate_prolog(struct nfp_dump_state *dump)
{
	struct nfp_dump_prolog *prolog = dump->p;
	u32 total_size;
	int err;

	total_size = ALIGN8(sizeof(*prolog));

	err = nfp_add_tlv(NFP_DUMPSPEC_TYPE_PROLOG, total_size, dump);
	if (err)
		return err;

	prolog->dump_level = dump->requested_level;

	return 0;
}