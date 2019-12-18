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
struct wsm_beacon_transmit {int enable_beaconing; } ;
struct cw1200_common {int dummy; } ;

/* Variables and functions */
 int wsm_beacon_transmit (struct cw1200_common*,struct wsm_beacon_transmit*) ; 

__attribute__((used)) static int cw1200_enable_beaconing(struct cw1200_common *priv,
				   bool enable)
{
	struct wsm_beacon_transmit transmit = {
		.enable_beaconing = enable,
	};

	return wsm_beacon_transmit(priv, &transmit);
}