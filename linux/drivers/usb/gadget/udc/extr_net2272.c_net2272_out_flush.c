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
struct net2272_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_OUT_NAKING (struct net2272_ep*) ; 
 int BUFFER_FLUSH ; 
 int DATA_OUT_TOKEN_INTERRUPT ; 
 int DATA_PACKET_RECEIVED_INTERRUPT ; 
 int /*<<< orphan*/  EP_STAT0 ; 
 int /*<<< orphan*/  EP_STAT1 ; 
 int /*<<< orphan*/  net2272_ep_write (struct net2272_ep*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
net2272_out_flush(struct net2272_ep *ep)
{
	ASSERT_OUT_NAKING(ep);

	net2272_ep_write(ep, EP_STAT0, (1 << DATA_OUT_TOKEN_INTERRUPT)
			| (1 << DATA_PACKET_RECEIVED_INTERRUPT));
	net2272_ep_write(ep, EP_STAT1, 1 << BUFFER_FLUSH);
}