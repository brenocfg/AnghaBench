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
struct nfp_bar {int dummy; } ;
struct nfp6000_pcie {int bars; struct nfp_bar* bar; } ;

/* Variables and functions */
 scalar_t__ matching_bar (struct nfp_bar*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static int
find_matching_bar(struct nfp6000_pcie *nfp,
		  u32 tgt, u32 act, u32 tok, u64 offset, size_t size, int width)
{
	int n;

	for (n = 0; n < nfp->bars; n++) {
		struct nfp_bar *bar = &nfp->bar[n];

		if (matching_bar(bar, tgt, act, tok, offset, size, width))
			return n;
	}

	return -1;
}