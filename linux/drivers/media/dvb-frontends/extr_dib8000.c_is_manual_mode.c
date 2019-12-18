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
struct dtv_frontend_properties {scalar_t__ delivery_system; scalar_t__ transmission_mode; scalar_t__ guard_interval; int isdbt_layer_enabled; TYPE_1__* layer; } ;
struct TYPE_2__ {int segment_count; scalar_t__ modulation; scalar_t__ fec; } ;

/* Variables and functions */
 scalar_t__ FEC_AUTO ; 
 scalar_t__ GUARD_INTERVAL_AUTO ; 
 scalar_t__ QAM_AUTO ; 
 scalar_t__ SYS_ISDBT ; 
 scalar_t__ TRANSMISSION_MODE_AUTO ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 

__attribute__((used)) static int is_manual_mode(struct dtv_frontend_properties *c)
{
	int i, n_segs = 0;

	/* Use auto mode on DVB-T compat mode */
	if (c->delivery_system != SYS_ISDBT)
		return 0;

	/*
	 * Transmission mode is only detected on auto mode, currently
	 */
	if (c->transmission_mode == TRANSMISSION_MODE_AUTO) {
		dprintk("transmission mode auto\n");
		return 0;
	}

	/*
	 * Guard interval is only detected on auto mode, currently
	 */
	if (c->guard_interval == GUARD_INTERVAL_AUTO) {
		dprintk("guard interval auto\n");
		return 0;
	}

	/*
	 * If no layer is enabled, assume auto mode, as at least one
	 * layer should be enabled
	 */
	if (!c->isdbt_layer_enabled) {
		dprintk("no layer modulation specified\n");
		return 0;
	}

	/*
	 * Check if the per-layer parameters aren't auto and
	 * disable a layer if segment count is 0 or invalid.
	 */
	for (i = 0; i < 3; i++) {
		if (!(c->isdbt_layer_enabled & 1 << i))
			continue;

		if ((c->layer[i].segment_count > 13) ||
		    (c->layer[i].segment_count == 0)) {
			c->isdbt_layer_enabled &= ~(1 << i);
			continue;
		}

		n_segs += c->layer[i].segment_count;

		if ((c->layer[i].modulation == QAM_AUTO) ||
		    (c->layer[i].fec == FEC_AUTO)) {
			dprintk("layer %c has either modulation or FEC auto\n",
				'A' + i);
			return 0;
		}
	}

	/*
	 * Userspace specified a wrong number of segments.
	 *	fallback to auto mode.
	 */
	if (n_segs == 0 || n_segs > 13) {
		dprintk("number of segments is invalid\n");
		return 0;
	}

	/* Everything looks ok for manual mode */
	return 1;
}