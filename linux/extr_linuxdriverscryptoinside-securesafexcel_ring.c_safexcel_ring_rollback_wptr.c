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
struct safexcel_desc_ring {scalar_t__ write; scalar_t__ read; scalar_t__ base; scalar_t__ base_end; scalar_t__ offset; } ;
struct safexcel_crypto_priv {int dummy; } ;

/* Variables and functions */

void safexcel_ring_rollback_wptr(struct safexcel_crypto_priv *priv,
				 struct safexcel_desc_ring *ring)
{
	if (ring->write == ring->read)
		return;

	if (ring->write == ring->base)
		ring->write = ring->base_end;
	else
		ring->write -= ring->offset;
}