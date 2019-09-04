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
struct dtv_frontend_properties {int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  tda665x_set_frequency (struct dvb_frontend*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tda665x_set_params(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;

	tda665x_set_frequency(fe, c->frequency);

	return 0;
}