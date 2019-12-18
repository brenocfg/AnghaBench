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
typedef  int /*<<< orphan*/  u8 ;
struct ef4_tx_queue {int dummy; } ;
struct ef4_tx_buffer {int dummy; } ;

/* Variables and functions */
 size_t EF4_TX_CB_SIZE ; 
 int /*<<< orphan*/ * ef4_tx_get_copy_buffer (struct ef4_tx_queue*,struct ef4_tx_buffer*) ; 

u8 *ef4_tx_get_copy_buffer_limited(struct ef4_tx_queue *tx_queue,
				   struct ef4_tx_buffer *buffer, size_t len)
{
	if (len > EF4_TX_CB_SIZE)
		return NULL;
	return ef4_tx_get_copy_buffer(tx_queue, buffer);
}