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
typedef  int /*<<< orphan*/  u8 ;
struct pfn_array {int dummy; } ;
struct channel_program {int /*<<< orphan*/  ccwchain_list; } ;
struct ccwchain {int ch_len; int /*<<< orphan*/  next; struct pfn_array* ch_pa; struct ccw1* ch_ccw; } ;
struct ccw1 {int dummy; } ;

/* Variables and functions */
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 struct ccwchain* kzalloc (size_t,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ccwchain *ccwchain_alloc(struct channel_program *cp, int len)
{
	struct ccwchain *chain;
	void *data;
	size_t size;

	/* Make ccw address aligned to 8. */
	size = ((sizeof(*chain) + 7L) & -8L) +
		sizeof(*chain->ch_ccw) * len +
		sizeof(*chain->ch_pa) * len;
	chain = kzalloc(size, GFP_DMA | GFP_KERNEL);
	if (!chain)
		return NULL;

	data = (u8 *)chain + ((sizeof(*chain) + 7L) & -8L);
	chain->ch_ccw = (struct ccw1 *)data;

	data = (u8 *)(chain->ch_ccw) + sizeof(*chain->ch_ccw) * len;
	chain->ch_pa = (struct pfn_array *)data;

	chain->ch_len = len;

	list_add_tail(&chain->next, &cp->ccwchain_list);

	return chain;
}