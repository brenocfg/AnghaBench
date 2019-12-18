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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  frequency_step_hz; } ;
struct TYPE_7__ {TYPE_2__ info; } ;
struct TYPE_5__ {int /*<<< orphan*/  frequency_stepsize_hz; } ;
struct TYPE_8__ {TYPE_3__ tuner_ops; TYPE_1__ info; } ;
struct dtv_frontend_properties {int delivery_system; } ;
struct dvb_frontend {TYPE_4__ ops; struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
#define  SYS_DVBS 131 
#define  SYS_DVBS2 130 
#define  SYS_ISDBS 129 
#define  SYS_TURBO 128 
 int /*<<< orphan*/  kHz ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 dvb_frontend_get_stepsize(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 fe_step = fe->ops.info.frequency_stepsize_hz;
	u32 tuner_step = fe->ops.tuner_ops.info.frequency_step_hz;
	u32 step = max(fe_step, tuner_step);

	switch (c->delivery_system) {
	case SYS_DVBS:
	case SYS_DVBS2:
	case SYS_TURBO:
	case SYS_ISDBS:
		step /= kHz;
		break;
	default:
		break;
	}

	return step;
}