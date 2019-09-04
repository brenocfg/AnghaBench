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
struct nvkm_instobj {int /*<<< orphan*/  head; } ;
struct nvkm_instmem {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
nvkm_instobj_dtor(struct nvkm_instmem *imem, struct nvkm_instobj *iobj)
{
	spin_lock(&imem->lock);
	list_del(&iobj->head);
	spin_unlock(&imem->lock);
}