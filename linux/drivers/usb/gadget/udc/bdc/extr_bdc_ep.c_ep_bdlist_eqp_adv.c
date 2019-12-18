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
struct TYPE_2__ {int eqp_bdi; int num_bds_table; int max_bdi; } ;
struct bdc_ep {TYPE_1__ bd_list; } ;

/* Variables and functions */

__attribute__((used)) static void ep_bdlist_eqp_adv(struct bdc_ep *ep)
{
	ep->bd_list.eqp_bdi++;
	/* if it's chain bd, then move to next */
	if (((ep->bd_list.eqp_bdi + 1) % ep->bd_list.num_bds_table) == 0)
		ep->bd_list.eqp_bdi++;

	/* if the eqp is pointing to last + 1 then move back to 0 */
	if (ep->bd_list.eqp_bdi == (ep->bd_list.max_bdi + 1))
		ep->bd_list.eqp_bdi = 0;
}