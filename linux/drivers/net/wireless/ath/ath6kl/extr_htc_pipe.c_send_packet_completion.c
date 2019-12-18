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
struct list_head {int dummy; } ;
struct htc_target {struct htc_endpoint* endpoint; } ;
struct htc_packet {size_t endpoint; int /*<<< orphan*/  list; } ;
struct htc_endpoint {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  do_send_completion (struct htc_endpoint*,struct list_head*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  restore_tx_packet (struct htc_packet*) ; 

__attribute__((used)) static void send_packet_completion(struct htc_target *target,
				   struct htc_packet *packet)
{
	struct htc_endpoint *ep = &target->endpoint[packet->endpoint];
	struct list_head container;

	restore_tx_packet(packet);
	INIT_LIST_HEAD(&container);
	list_add_tail(&packet->list, &container);

	/* do completion */
	do_send_completion(ep, &container);
}