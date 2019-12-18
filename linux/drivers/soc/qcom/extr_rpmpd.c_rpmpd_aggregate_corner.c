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
struct rpmpd {int /*<<< orphan*/  corner; scalar_t__ enabled; struct rpmpd* peer; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCOM_SMD_RPM_ACTIVE_STATE ; 
 int /*<<< orphan*/  QCOM_SMD_RPM_SLEEP_STATE ; 
 unsigned int max (unsigned int,unsigned int) ; 
 int rpmpd_send_corner (struct rpmpd*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  to_active_sleep (struct rpmpd*,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int rpmpd_aggregate_corner(struct rpmpd *pd)
{
	int ret;
	struct rpmpd *peer = pd->peer;
	unsigned int active_corner, sleep_corner;
	unsigned int this_active_corner = 0, this_sleep_corner = 0;
	unsigned int peer_active_corner = 0, peer_sleep_corner = 0;

	to_active_sleep(pd, pd->corner, &this_active_corner, &this_sleep_corner);

	if (peer && peer->enabled)
		to_active_sleep(peer, peer->corner, &peer_active_corner,
				&peer_sleep_corner);

	active_corner = max(this_active_corner, peer_active_corner);

	ret = rpmpd_send_corner(pd, QCOM_SMD_RPM_ACTIVE_STATE, active_corner);
	if (ret)
		return ret;

	sleep_corner = max(this_sleep_corner, peer_sleep_corner);

	return rpmpd_send_corner(pd, QCOM_SMD_RPM_SLEEP_STATE, sleep_corner);
}