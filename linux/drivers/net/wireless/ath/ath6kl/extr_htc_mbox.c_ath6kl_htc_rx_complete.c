#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct htc_packet {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rx ) (int /*<<< orphan*/ ,struct htc_packet*) ;} ;
struct htc_endpoint {int /*<<< orphan*/  target; TYPE_1__ ep_cb; int /*<<< orphan*/  eid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_HTC ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct htc_packet*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct htc_packet*) ; 

__attribute__((used)) static void ath6kl_htc_rx_complete(struct htc_endpoint *endpoint,
				   struct htc_packet *packet)
{
		ath6kl_dbg(ATH6KL_DBG_HTC,
			   "htc rx complete ep %d packet 0x%p\n",
			   endpoint->eid, packet);

		endpoint->ep_cb.rx(endpoint->target, packet);
}