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
struct dtv_frontend_properties {scalar_t__ delivery_system; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
 scalar_t__ SYS_DVBC_ANNEX_A ; 
 scalar_t__ SYS_DVBT ; 
 scalar_t__ SYS_DVBT2 ; 
 scalar_t__ SYS_ISDBT ; 
 int helene_set_params_s (struct dvb_frontend*) ; 
 int helene_set_params_t (struct dvb_frontend*) ; 

__attribute__((used)) static int helene_set_params(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;

	if (p->delivery_system == SYS_DVBT ||
	    p->delivery_system == SYS_DVBT2 ||
	    p->delivery_system == SYS_ISDBT ||
	    p->delivery_system == SYS_DVBC_ANNEX_A)
		return helene_set_params_t(fe);

	return helene_set_params_s(fe);
}