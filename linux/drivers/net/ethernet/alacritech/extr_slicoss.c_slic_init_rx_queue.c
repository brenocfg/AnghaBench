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
struct slic_rx_queue {struct slic_rx_buffer* rxbuffs; int /*<<< orphan*/  len; scalar_t__ put_idx; scalar_t__ done_idx; } ;
struct slic_rx_buffer {int dummy; } ;
struct slic_device {struct slic_rx_queue rxq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SLIC_NUM_RX_LES ; 
 struct slic_rx_buffer* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slic_refill_rx_queue (struct slic_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int slic_init_rx_queue(struct slic_device *sdev)
{
	struct slic_rx_queue *rxq = &sdev->rxq;
	struct slic_rx_buffer *buff;

	rxq->len = SLIC_NUM_RX_LES;
	rxq->done_idx = 0;
	rxq->put_idx = 0;

	buff = kcalloc(rxq->len, sizeof(*buff), GFP_KERNEL);
	if (!buff)
		return -ENOMEM;

	rxq->rxbuffs = buff;
	slic_refill_rx_queue(sdev, GFP_KERNEL);

	return 0;
}