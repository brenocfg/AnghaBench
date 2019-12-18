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
struct tse_buffer {int dummy; } ;
struct altera_tse_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_rx (struct altera_tse_private*,struct tse_buffer*) ; 

void sgdma_add_rx_desc(struct altera_tse_private *priv,
		       struct tse_buffer *rxbuffer)
{
	queue_rx(priv, rxbuffer);
}