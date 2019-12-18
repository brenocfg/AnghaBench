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
struct mn88443x_priv {int dummy; } ;
struct dtv_frontend_properties {scalar_t__ delivery_system; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct mn88443x_priv* demodulator_priv; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SYS_ISDBS ; 
 scalar_t__ SYS_ISDBT ; 
 int mn88443x_s_read_status (struct mn88443x_priv*,struct dtv_frontend_properties*,int*) ; 
 int mn88443x_t_read_status (struct mn88443x_priv*,struct dtv_frontend_properties*,int*) ; 

__attribute__((used)) static int mn88443x_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct mn88443x_priv *chip = fe->demodulator_priv;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;

	if (c->delivery_system == SYS_ISDBS)
		return mn88443x_s_read_status(chip, c, status);

	if (c->delivery_system == SYS_ISDBT)
		return mn88443x_t_read_status(chip, c, status);

	return -EINVAL;
}