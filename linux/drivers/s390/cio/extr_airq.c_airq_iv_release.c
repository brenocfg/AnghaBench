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
struct airq_iv {int flags; struct airq_iv* avail; int /*<<< orphan*/  bits; int /*<<< orphan*/  vector; int /*<<< orphan*/  vector_dma; struct airq_iv* bitlock; struct airq_iv* ptr; struct airq_iv* data; } ;

/* Variables and functions */
 int AIRQ_IV_CACHELINE ; 
 int /*<<< orphan*/  airq_iv_cache ; 
 int /*<<< orphan*/  cio_dma_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iv_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct airq_iv*) ; 

void airq_iv_release(struct airq_iv *iv)
{
	kfree(iv->data);
	kfree(iv->ptr);
	kfree(iv->bitlock);
	if (iv->flags & AIRQ_IV_CACHELINE)
		dma_pool_free(airq_iv_cache, iv->vector, iv->vector_dma);
	else
		cio_dma_free(iv->vector, iv_size(iv->bits));
	kfree(iv->avail);
	kfree(iv);
}