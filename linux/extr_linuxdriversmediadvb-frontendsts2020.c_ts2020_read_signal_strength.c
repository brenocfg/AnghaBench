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
typedef  unsigned int u16 ;
struct TYPE_4__ {int /*<<< orphan*/  work; } ;
struct ts2020_priv {TYPE_1__ stat_work; scalar_t__ dont_poll; } ;
struct TYPE_6__ {TYPE_2__* stat; } ;
struct dtv_frontend_properties {TYPE_3__ strength; } ;
struct dvb_frontend {struct ts2020_priv* tuner_priv; struct dtv_frontend_properties dtv_property_cache; } ;
typedef  int __s64 ;
struct TYPE_5__ {scalar_t__ scale; int svalue; } ;

/* Variables and functions */
 scalar_t__ FE_SCALE_NOT_AVAILABLE ; 
 int div64_s64 (int,int) ; 
 int /*<<< orphan*/  ts2020_stat_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ts2020_read_signal_strength(struct dvb_frontend *fe,
				       u16 *_signal_strength)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	struct ts2020_priv *priv = fe->tuner_priv;
	unsigned strength;
	__s64 gain;

	if (priv->dont_poll)
		ts2020_stat_work(&priv->stat_work.work);

	if (c->strength.stat[0].scale == FE_SCALE_NOT_AVAILABLE) {
		*_signal_strength = 0;
		return 0;
	}

	gain = c->strength.stat[0].svalue;

	/* Calculate the signal strength based on the total gain of the tuner */
	if (gain < -85000)
		/* 0%: no signal or weak signal */
		strength = 0;
	else if (gain < -65000)
		/* 0% - 60%: weak signal */
		strength = 0 + div64_s64((85000 + gain) * 3, 1000);
	else if (gain < -45000)
		/* 60% - 90%: normal signal */
		strength = 60 + div64_s64((65000 + gain) * 3, 2000);
	else
		/* 90% - 99%: strong signal */
		strength = 90 + div64_s64((45000 + gain), 5000);

	*_signal_strength = strength * 65535 / 100;
	return 0;
}