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
struct mvneta_rx_queue {int first_to_refill; int refill_num; int /*<<< orphan*/  refill_err; int /*<<< orphan*/  id; struct mvneta_rx_desc* descs; } ;
struct mvneta_rx_desc {int /*<<< orphan*/  buf_phys_addr; } ;
struct mvneta_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MVNETA_QUEUE_NEXT_DESC (struct mvneta_rx_queue*,int) ; 
 scalar_t__ mvneta_rx_refill (struct mvneta_port*,struct mvneta_rx_desc*,struct mvneta_rx_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline
int mvneta_rx_refill_queue(struct mvneta_port *pp, struct mvneta_rx_queue *rxq)
{
	struct mvneta_rx_desc *rx_desc;
	int curr_desc = rxq->first_to_refill;
	int i;

	for (i = 0; (i < rxq->refill_num) && (i < 64); i++) {
		rx_desc = rxq->descs + curr_desc;
		if (!(rx_desc->buf_phys_addr)) {
			if (mvneta_rx_refill(pp, rx_desc, rxq, GFP_ATOMIC)) {
				pr_err("Can't refill queue %d. Done %d from %d\n",
				       rxq->id, i, rxq->refill_num);
				rxq->refill_err++;
				break;
			}
		}
		curr_desc = MVNETA_QUEUE_NEXT_DESC(rxq, curr_desc);
	}
	rxq->refill_num -= i;
	rxq->first_to_refill = curr_desc;

	return i;
}