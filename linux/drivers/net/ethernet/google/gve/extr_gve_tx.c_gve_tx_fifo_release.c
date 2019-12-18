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
struct gve_tx_fifo {scalar_t__ size; int /*<<< orphan*/  base; int /*<<< orphan*/  available; } ;
struct gve_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gve_tx_fifo_release(struct gve_priv *priv, struct gve_tx_fifo *fifo)
{
	WARN(atomic_read(&fifo->available) != fifo->size,
	     "Releasing non-empty fifo");

	vunmap(fifo->base);
}