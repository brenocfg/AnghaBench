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
struct vrfb {int context; scalar_t__* paddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DBG (char*,int) ; 
 int /*<<< orphan*/  OMAP_VRFB_SIZE ; 
 int /*<<< orphan*/  clear_bit (int,int*) ; 
 int /*<<< orphan*/  ctx_lock ; 
 int ctx_map ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,int /*<<< orphan*/ ) ; 

void omap_vrfb_release_ctx(struct vrfb *vrfb)
{
	int rot;
	int ctx = vrfb->context;

	if (ctx == 0xff)
		return;

	DBG("release ctx %d\n", ctx);

	mutex_lock(&ctx_lock);

	BUG_ON(!(ctx_map & (1 << ctx)));

	clear_bit(ctx, &ctx_map);

	for (rot = 0; rot < 4; ++rot) {
		if (vrfb->paddr[rot]) {
			release_mem_region(vrfb->paddr[rot], OMAP_VRFB_SIZE);
			vrfb->paddr[rot] = 0;
		}
	}

	vrfb->context = 0xff;

	mutex_unlock(&ctx_lock);
}