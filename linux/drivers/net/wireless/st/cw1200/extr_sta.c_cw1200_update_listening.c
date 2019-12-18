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
struct cw1200_common {scalar_t__ join_status; } ;

/* Variables and functions */
 scalar_t__ CW1200_JOIN_STATUS_MONITOR ; 
 scalar_t__ CW1200_JOIN_STATUS_PASSIVE ; 
 int /*<<< orphan*/  cw1200_disable_listening (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_enable_listening (struct cw1200_common*) ; 
 int /*<<< orphan*/  wsm_set_probe_responder (struct cw1200_common*,int) ; 

void cw1200_update_listening(struct cw1200_common *priv, bool enabled)
{
	if (enabled) {
		if (priv->join_status == CW1200_JOIN_STATUS_PASSIVE) {
			if (!cw1200_enable_listening(priv))
				priv->join_status = CW1200_JOIN_STATUS_MONITOR;
			wsm_set_probe_responder(priv, true);
		}
	} else {
		if (priv->join_status == CW1200_JOIN_STATUS_MONITOR) {
			if (!cw1200_disable_listening(priv))
				priv->join_status = CW1200_JOIN_STATUS_PASSIVE;
			wsm_set_probe_responder(priv, false);
		}
	}
}