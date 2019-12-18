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
struct htc_target {int dummy; } ;
struct htc_packet {int /*<<< orphan*/  list; } ;
struct htc_endpoint {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  do_recv_completion (struct htc_endpoint*,struct list_head*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static void recv_packet_completion(struct htc_target *target,
				   struct htc_endpoint *ep,
				   struct htc_packet *packet)
{
	struct list_head container;
	INIT_LIST_HEAD(&container);
	list_add_tail(&packet->list, &container);

	/* do completion */
	do_recv_completion(ep, &container);
}