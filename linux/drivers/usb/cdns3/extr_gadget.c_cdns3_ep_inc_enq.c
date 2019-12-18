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
struct cdns3_endpoint {int /*<<< orphan*/  num_trbs; int /*<<< orphan*/  pcs; int /*<<< orphan*/  enqueue; int /*<<< orphan*/  free_trbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdns3_ep_inc_trb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cdns3_ep_inc_enq(struct cdns3_endpoint *priv_ep)
{
	priv_ep->free_trbs--;
	cdns3_ep_inc_trb(&priv_ep->enqueue, &priv_ep->pcs, priv_ep->num_trbs);
}