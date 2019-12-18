#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rvu {int dummy; } ;
struct TYPE_2__ {int in_use; int total; int /*<<< orphan*/ * cfg; } ;
struct nix_hw {TYPE_1__ mark_format; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  NIX_AF_MARK_FORMATX_CTL (int) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rvu_nix_reserve_mark_format(struct rvu *rvu, struct nix_hw *nix_hw,
				int blkaddr, u32 cfg)
{
	int fmt_idx;

	for (fmt_idx = 0; fmt_idx < nix_hw->mark_format.in_use; fmt_idx++) {
		if (nix_hw->mark_format.cfg[fmt_idx] == cfg)
			return fmt_idx;
	}
	if (fmt_idx >= nix_hw->mark_format.total)
		return -ERANGE;

	rvu_write64(rvu, blkaddr, NIX_AF_MARK_FORMATX_CTL(fmt_idx), cfg);
	nix_hw->mark_format.cfg[fmt_idx] = cfg;
	nix_hw->mark_format.in_use++;
	return fmt_idx;
}