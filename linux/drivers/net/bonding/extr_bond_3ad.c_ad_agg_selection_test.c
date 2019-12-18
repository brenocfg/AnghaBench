#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct aggregator {int /*<<< orphan*/  lag_ports; TYPE_4__* slave; scalar_t__ is_individual; } ;
struct TYPE_8__ {TYPE_3__* dev; TYPE_2__* bond; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  BOND_AD_BANDWIDTH 130 
#define  BOND_AD_COUNT 129 
#define  BOND_AD_STABLE 128 
 int /*<<< orphan*/  __agg_active_ports (struct aggregator*) ; 
 scalar_t__ __agg_has_partner (struct aggregator*) ; 
 int /*<<< orphan*/  __get_agg_bandwidth (struct aggregator*) ; 
 int __get_agg_selection_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_warn_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct aggregator *ad_agg_selection_test(struct aggregator *best,
						struct aggregator *curr)
{
	/* 0. If no best, select current.
	 *
	 * 1. If the current agg is not individual, and the best is
	 *    individual, select current.
	 *
	 * 2. If current agg is individual and the best is not, keep best.
	 *
	 * 3. Therefore, current and best are both individual or both not
	 *    individual, so:
	 *
	 * 3a. If current agg partner replied, and best agg partner did not,
	 *     select current.
	 *
	 * 3b. If current agg partner did not reply and best agg partner
	 *     did reply, keep best.
	 *
	 * 4.  Therefore, current and best both have partner replies or
	 *     both do not, so perform selection policy:
	 *
	 * BOND_AD_COUNT: Select by count of ports.  If count is equal,
	 *     select by bandwidth.
	 *
	 * BOND_AD_STABLE, BOND_AD_BANDWIDTH: Select by bandwidth.
	 */
	if (!best)
		return curr;

	if (!curr->is_individual && best->is_individual)
		return curr;

	if (curr->is_individual && !best->is_individual)
		return best;

	if (__agg_has_partner(curr) && !__agg_has_partner(best))
		return curr;

	if (!__agg_has_partner(curr) && __agg_has_partner(best))
		return best;

	switch (__get_agg_selection_mode(curr->lag_ports)) {
	case BOND_AD_COUNT:
		if (__agg_active_ports(curr) > __agg_active_ports(best))
			return curr;

		if (__agg_active_ports(curr) < __agg_active_ports(best))
			return best;

		/*FALLTHROUGH*/
	case BOND_AD_STABLE:
	case BOND_AD_BANDWIDTH:
		if (__get_agg_bandwidth(curr) > __get_agg_bandwidth(best))
			return curr;

		break;

	default:
		net_warn_ratelimited("%s: (slave %s): Impossible agg select mode %d\n",
				     curr->slave->bond->dev->name,
				     curr->slave->dev->name,
				     __get_agg_selection_mode(curr->lag_ports));
		break;
	}

	return best;
}