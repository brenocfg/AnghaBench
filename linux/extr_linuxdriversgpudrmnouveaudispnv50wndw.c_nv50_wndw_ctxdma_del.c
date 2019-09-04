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
struct nv50_wndw_ctxdma {int /*<<< orphan*/  head; int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nv50_wndw_ctxdma*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvif_object_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nv50_wndw_ctxdma_del(struct nv50_wndw_ctxdma *ctxdma)
{
	nvif_object_fini(&ctxdma->object);
	list_del(&ctxdma->head);
	kfree(ctxdma);
}