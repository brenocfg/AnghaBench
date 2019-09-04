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
typedef  int ulong ;
struct aoetgt {int dummy; } ;
struct aoedev {int ntargets; struct aoetgt** targets; struct aoetgt** tgt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct aoetgt** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct aoetgt**) ; 
 int /*<<< orphan*/  memmove (struct aoetgt**,struct aoetgt**,int) ; 

__attribute__((used)) static struct aoetgt **
grow_targets(struct aoedev *d)
{
	ulong oldn, newn;
	struct aoetgt **tt;

	oldn = d->ntargets;
	newn = oldn * 2;
	tt = kcalloc(newn, sizeof(*d->targets), GFP_ATOMIC);
	if (!tt)
		return NULL;
	memmove(tt, d->targets, sizeof(*d->targets) * oldn);
	d->tgt = tt + (d->tgt - d->targets);
	kfree(d->targets);
	d->targets = tt;
	d->ntargets = newn;

	return &d->targets[oldn];
}