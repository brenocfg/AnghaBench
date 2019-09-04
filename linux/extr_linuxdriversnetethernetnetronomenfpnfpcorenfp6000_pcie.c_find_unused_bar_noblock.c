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
struct nfp_bar {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  bitsize; } ;
struct nfp6000_pcie {int bars; struct nfp_bar* bar; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 scalar_t__ WARN (int,char*,int,int,int,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int compute_bar (struct nfp6000_pcie const*,struct nfp_bar const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static int
find_unused_bar_noblock(const struct nfp6000_pcie *nfp,
			int tgt, int act, int tok,
			u64 offset, size_t size, int width)
{
	int n, busy = 0;

	for (n = 0; n < nfp->bars; n++) {
		const struct nfp_bar *bar = &nfp->bar[n];
		int err;

		if (!bar->bitsize)
			continue;

		/* Just check to see if we can make it fit... */
		err = compute_bar(nfp, bar, NULL, NULL,
				  tgt, act, tok, offset, size, width);
		if (err)
			continue;

		if (!atomic_read(&bar->refcnt))
			return n;

		busy++;
	}

	if (WARN(!busy, "No suitable BAR found for request tgt:0x%x act:0x%x tok:0x%x off:0x%llx size:%zd width:%d\n",
		 tgt, act, tok, offset, size, width))
		return -EINVAL;

	return -EAGAIN;
}