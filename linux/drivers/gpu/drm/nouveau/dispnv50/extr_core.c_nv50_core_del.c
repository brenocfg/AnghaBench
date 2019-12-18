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
struct nv50_core {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nv50_core*) ; 
 int /*<<< orphan*/  nv50_dmac_destroy (int /*<<< orphan*/ *) ; 

void
nv50_core_del(struct nv50_core **pcore)
{
	struct nv50_core *core = *pcore;
	if (core) {
		nv50_dmac_destroy(&core->chan);
		kfree(*pcore);
		*pcore = NULL;
	}
}