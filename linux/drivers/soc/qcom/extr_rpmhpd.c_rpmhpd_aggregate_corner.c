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
struct rpmhpd {unsigned int corner; unsigned int active_corner; scalar_t__ enabled; struct rpmhpd* peer; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPMH_ACTIVE_ONLY_STATE ; 
 int /*<<< orphan*/  RPMH_SLEEP_STATE ; 
 int /*<<< orphan*/  RPMH_WAKE_ONLY_STATE ; 
 unsigned int max (unsigned int,unsigned int) ; 
 int rpmhpd_send_corner (struct rpmhpd*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  to_active_sleep (struct rpmhpd*,unsigned int,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int rpmhpd_aggregate_corner(struct rpmhpd *pd, unsigned int corner)
{
	int ret;
	struct rpmhpd *peer = pd->peer;
	unsigned int active_corner, sleep_corner;
	unsigned int this_active_corner = 0, this_sleep_corner = 0;
	unsigned int peer_active_corner = 0, peer_sleep_corner = 0;

	to_active_sleep(pd, corner, &this_active_corner, &this_sleep_corner);

	if (peer && peer->enabled)
		to_active_sleep(peer, peer->corner, &peer_active_corner,
				&peer_sleep_corner);

	active_corner = max(this_active_corner, peer_active_corner);

	ret = rpmhpd_send_corner(pd, RPMH_ACTIVE_ONLY_STATE, active_corner,
				 active_corner > pd->active_corner);
	if (ret)
		return ret;

	pd->active_corner = active_corner;

	if (peer) {
		peer->active_corner = active_corner;

		ret = rpmhpd_send_corner(pd, RPMH_WAKE_ONLY_STATE,
					 active_corner, false);
		if (ret)
			return ret;

		sleep_corner = max(this_sleep_corner, peer_sleep_corner);

		return rpmhpd_send_corner(pd, RPMH_SLEEP_STATE, sleep_corner,
					  false);
	}

	return ret;
}