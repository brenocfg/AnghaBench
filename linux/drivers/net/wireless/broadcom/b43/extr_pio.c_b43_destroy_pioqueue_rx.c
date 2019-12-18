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
struct b43_pio_rxqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct b43_pio_rxqueue*) ; 

__attribute__((used)) static void b43_destroy_pioqueue_rx(struct b43_pio_rxqueue *q,
				    const char *name)
{
	if (!q)
		return;
	kfree(q);
}