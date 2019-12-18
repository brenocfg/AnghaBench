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
struct wil_status_ring {size_t elem_size; size_t size; int /*<<< orphan*/ * va; int /*<<< orphan*/  pa; } ;
struct wil6210_priv {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,size_t,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct device* wil_to_dev (struct wil6210_priv*) ; 

__attribute__((used)) static void wil_sring_free(struct wil6210_priv *wil,
			   struct wil_status_ring *sring)
{
	struct device *dev = wil_to_dev(wil);
	size_t sz;

	if (!sring || !sring->va)
		return;

	sz = sring->elem_size * sring->size;

	wil_dbg_misc(wil, "status_ring_free, size(bytes)=%zu, 0x%p:%pad\n",
		     sz, sring->va, &sring->pa);

	dma_free_coherent(dev, sz, (void *)sring->va, sring->pa);
	sring->pa = 0;
	sring->va = NULL;
}