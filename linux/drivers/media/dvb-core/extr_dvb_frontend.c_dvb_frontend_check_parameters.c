#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_5__ {scalar_t__ symbol_rate_min; scalar_t__ symbol_rate_max; } ;
struct TYPE_6__ {TYPE_2__ info; } ;
struct dtv_frontend_properties {scalar_t__ frequency; int delivery_system; scalar_t__ symbol_rate; } ;
struct dvb_frontend {TYPE_3__ ops; int /*<<< orphan*/  id; TYPE_1__* dvb; struct dtv_frontend_properties dtv_property_cache; } ;
struct TYPE_4__ {int /*<<< orphan*/  num; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SYS_DVBC_ANNEX_A 132 
#define  SYS_DVBC_ANNEX_C 131 
#define  SYS_DVBS 130 
#define  SYS_DVBS2 129 
#define  SYS_TURBO 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dvb_frontend_get_frequency_limits (struct dvb_frontend*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dvb_frontend_check_parameters(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 freq_min;
	u32 freq_max;

	/* range check: frequency */
	dvb_frontend_get_frequency_limits(fe, &freq_min, &freq_max, NULL);
	if ((freq_min && c->frequency < freq_min) ||
	    (freq_max && c->frequency > freq_max)) {
		dev_warn(fe->dvb->device, "DVB: adapter %i frontend %i frequency %u out of range (%u..%u)\n",
			 fe->dvb->num, fe->id, c->frequency,
			 freq_min, freq_max);
		return -EINVAL;
	}

	/* range check: symbol rate */
	switch (c->delivery_system) {
	case SYS_DVBS:
	case SYS_DVBS2:
	case SYS_TURBO:
	case SYS_DVBC_ANNEX_A:
	case SYS_DVBC_ANNEX_C:
		if ((fe->ops.info.symbol_rate_min &&
		     c->symbol_rate < fe->ops.info.symbol_rate_min) ||
		    (fe->ops.info.symbol_rate_max &&
		     c->symbol_rate > fe->ops.info.symbol_rate_max)) {
			dev_warn(fe->dvb->device, "DVB: adapter %i frontend %i symbol rate %u out of range (%u..%u)\n",
				 fe->dvb->num, fe->id, c->symbol_rate,
				 fe->ops.info.symbol_rate_min,
				 fe->ops.info.symbol_rate_max);
			return -EINVAL;
		}
	default:
		break;
	}

	return 0;
}