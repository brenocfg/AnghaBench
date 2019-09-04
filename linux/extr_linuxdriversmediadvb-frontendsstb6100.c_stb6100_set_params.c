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
struct dtv_frontend_properties {scalar_t__ frequency; scalar_t__ bandwidth_hz; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  stb6100_set_bandwidth (struct dvb_frontend*,scalar_t__) ; 
 int /*<<< orphan*/  stb6100_set_frequency (struct dvb_frontend*,scalar_t__) ; 

__attribute__((used)) static int stb6100_set_params(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;

	if (c->frequency > 0)
		stb6100_set_frequency(fe, c->frequency);

	if (c->bandwidth_hz > 0)
		stb6100_set_bandwidth(fe, c->bandwidth_hz);

	return 0;
}