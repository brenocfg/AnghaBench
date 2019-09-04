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
struct pool_features {scalar_t__ mode; int error_if_no_space; int /*<<< orphan*/  discard_passdown; int /*<<< orphan*/  discard_enabled; int /*<<< orphan*/  zero_new_blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMEMIT (char*,...) ; 
 scalar_t__ PM_READ_ONLY ; 

__attribute__((used)) static void emit_flags(struct pool_features *pf, char *result,
		       unsigned sz, unsigned maxlen)
{
	unsigned count = !pf->zero_new_blocks + !pf->discard_enabled +
		!pf->discard_passdown + (pf->mode == PM_READ_ONLY) +
		pf->error_if_no_space;
	DMEMIT("%u ", count);

	if (!pf->zero_new_blocks)
		DMEMIT("skip_block_zeroing ");

	if (!pf->discard_enabled)
		DMEMIT("ignore_discard ");

	if (!pf->discard_passdown)
		DMEMIT("no_discard_passdown ");

	if (pf->mode == PM_READ_ONLY)
		DMEMIT("read_only ");

	if (pf->error_if_no_space)
		DMEMIT("error_if_no_space ");
}