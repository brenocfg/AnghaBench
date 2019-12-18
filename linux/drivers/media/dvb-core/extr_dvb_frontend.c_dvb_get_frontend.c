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
struct dvb_frontend_parameters {int dummy; } ;
struct dvb_frontend {int /*<<< orphan*/  dtv_property_cache; } ;
struct dtv_frontend_properties {int dummy; } ;
typedef  int /*<<< orphan*/  getp ;

/* Variables and functions */
 int dtv_get_frontend (struct dvb_frontend*,struct dtv_frontend_properties*,struct dvb_frontend_parameters*) ; 
 int /*<<< orphan*/  memcpy (struct dtv_frontend_properties*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dvb_get_frontend(struct dvb_frontend *fe,
			    struct dvb_frontend_parameters *p_out)
{
	struct dtv_frontend_properties getp;

	/*
	 * Let's use our own copy of property cache, in order to
	 * avoid mangling with DTV zigzag logic, as drivers might
	 * return crap, if they don't check if the data is available
	 * before updating the properties cache.
	 */
	memcpy(&getp, &fe->dtv_property_cache, sizeof(getp));

	return dtv_get_frontend(fe, &getp, p_out);
}