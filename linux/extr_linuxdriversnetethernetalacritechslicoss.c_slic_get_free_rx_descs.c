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
struct slic_rx_queue {int /*<<< orphan*/  len; int /*<<< orphan*/  done_idx; int /*<<< orphan*/  put_idx; } ;

/* Variables and functions */
 unsigned int slic_get_free_queue_descs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int slic_get_free_rx_descs(struct slic_rx_queue *rxq)
{
	return slic_get_free_queue_descs(rxq->put_idx, rxq->done_idx, rxq->len);
}