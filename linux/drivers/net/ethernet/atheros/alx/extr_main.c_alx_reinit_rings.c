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
struct alx_priv {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alx_free_buffers (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_init_ring_ptrs (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_refill_rx_ring (struct alx_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alx_reinit_rings(struct alx_priv *alx)
{
	alx_free_buffers(alx);

	alx_init_ring_ptrs(alx);

	if (!alx_refill_rx_ring(alx, GFP_KERNEL))
		return -ENOMEM;

	return 0;
}