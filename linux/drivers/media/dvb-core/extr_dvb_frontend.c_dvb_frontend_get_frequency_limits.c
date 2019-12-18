#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_9__ {scalar_t__ frequency_min_hz; scalar_t__ frequency_max_hz; scalar_t__ frequency_tolerance_hz; } ;
struct TYPE_6__ {scalar_t__ frequency_min_hz; scalar_t__ frequency_max_hz; } ;
struct TYPE_7__ {TYPE_1__ info; } ;
struct TYPE_10__ {TYPE_4__ info; TYPE_2__ tuner_ops; } ;
struct dtv_frontend_properties {int delivery_system; } ;
struct dvb_frontend {TYPE_5__ ops; TYPE_3__* dvb; int /*<<< orphan*/  id; struct dtv_frontend_properties dtv_property_cache; } ;
struct TYPE_8__ {int /*<<< orphan*/  device; int /*<<< orphan*/  num; } ;

/* Variables and functions */
#define  SYS_DVBS 131 
#define  SYS_DVBS2 130 
#define  SYS_ISDBS 129 
#define  SYS_TURBO 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kHz ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void dvb_frontend_get_frequency_limits(struct dvb_frontend *fe,
					      u32 *freq_min, u32 *freq_max,
					      u32 *tolerance)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 tuner_min = fe->ops.tuner_ops.info.frequency_min_hz;
	u32 tuner_max = fe->ops.tuner_ops.info.frequency_max_hz;
	u32 frontend_min = fe->ops.info.frequency_min_hz;
	u32 frontend_max = fe->ops.info.frequency_max_hz;

	*freq_min = max(frontend_min, tuner_min);

	if (frontend_max == 0)
		*freq_max = tuner_max;
	else if (tuner_max == 0)
		*freq_max = frontend_max;
	else
		*freq_max = min(frontend_max, tuner_max);

	if (*freq_min == 0 || *freq_max == 0)
		dev_warn(fe->dvb->device,
			 "DVB: adapter %i frontend %u frequency limits undefined - fix the driver\n",
			 fe->dvb->num, fe->id);

	dev_dbg(fe->dvb->device, "frequency interval: tuner: %u...%u, frontend: %u...%u",
		tuner_min, tuner_max, frontend_min, frontend_max);

	/* If the standard is for satellite, convert frequencies to kHz */
	switch (c->delivery_system) {
	case SYS_DVBS:
	case SYS_DVBS2:
	case SYS_TURBO:
	case SYS_ISDBS:
		*freq_min /= kHz;
		*freq_max /= kHz;
		if (tolerance)
			*tolerance = fe->ops.info.frequency_tolerance_hz / kHz;

		break;
	default:
		if (tolerance)
			*tolerance = fe->ops.info.frequency_tolerance_hz;
		break;
	}
}