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
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ pio_rx_frame (struct b43_pio_rxqueue*) ; 

void b43_pio_rx(struct b43_pio_rxqueue *q)
{
	unsigned int count = 0;
	bool stop;

	while (1) {
		stop = (pio_rx_frame(q) == 0);
		if (stop)
			break;
		cond_resched();
		if (WARN_ON_ONCE(++count > 10000))
			break;
	}
}