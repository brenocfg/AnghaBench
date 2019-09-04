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
struct bufdesc_prop {int dsize; struct bufdesc* base; struct bufdesc* last; } ;
struct bufdesc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct bufdesc *fec_enet_get_nextdesc(struct bufdesc *bdp,
					     struct bufdesc_prop *bd)
{
	return (bdp >= bd->last) ? bd->base
			: (struct bufdesc *)(((void *)bdp) + bd->dsize);
}