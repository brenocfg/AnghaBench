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
struct ef4_tx_queue {int /*<<< orphan*/  txd; int /*<<< orphan*/  efx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ef4_free_special_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ef4_farch_tx_remove(struct ef4_tx_queue *tx_queue)
{
	ef4_free_special_buffer(tx_queue->efx, &tx_queue->txd);
}