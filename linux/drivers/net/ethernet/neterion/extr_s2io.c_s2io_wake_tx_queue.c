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
typedef  scalar_t__ u8 ;
struct fifo_info {scalar_t__ queue_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  fifo_no; } ;

/* Variables and functions */
 scalar_t__ FIFO_QUEUE_START ; 
 scalar_t__ FIFO_QUEUE_STOP ; 
 scalar_t__ __netif_subqueue_stopped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_subqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void s2io_wake_tx_queue(
	struct fifo_info *fifo, int cnt, u8 multiq)
{

	if (multiq) {
		if (cnt && __netif_subqueue_stopped(fifo->dev, fifo->fifo_no))
			netif_wake_subqueue(fifo->dev, fifo->fifo_no);
	} else if (cnt && (fifo->queue_state == FIFO_QUEUE_STOP)) {
		if (netif_queue_stopped(fifo->dev)) {
			fifo->queue_state = FIFO_QUEUE_START;
			netif_wake_queue(fifo->dev);
		}
	}
}