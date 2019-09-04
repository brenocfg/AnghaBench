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
struct safexcel_desc_ring {int /*<<< orphan*/  offset; void* read; void* base; void* base_end; void* write; } ;
struct safexcel_crypto_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 

void *safexcel_ring_next_rptr(struct safexcel_crypto_priv *priv,
			      struct safexcel_desc_ring *ring)
{
	void *ptr = ring->read;

	if (ring->write == ring->read)
		return ERR_PTR(-ENOENT);

	if (ring->read == ring->base_end)
		ring->read = ring->base;
	else
		ring->read += ring->offset;

	return ptr;
}