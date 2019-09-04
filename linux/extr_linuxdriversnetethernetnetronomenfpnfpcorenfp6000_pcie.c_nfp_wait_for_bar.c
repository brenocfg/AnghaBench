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
struct nfp6000_pcie {int /*<<< orphan*/  bar_waiters; } ;

/* Variables and functions */
 int EAGAIN ; 
 int find_unused_bar_and_lock (struct nfp6000_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nfp_wait_for_bar(struct nfp6000_pcie *nfp, int *barnum,
		 u32 tgt, u32 act, u32 tok, u64 offset, size_t size, int width)
{
	return wait_event_interruptible(nfp->bar_waiters,
		(*barnum = find_unused_bar_and_lock(nfp, tgt, act, tok,
						    offset, size, width))
					!= -EAGAIN);
}