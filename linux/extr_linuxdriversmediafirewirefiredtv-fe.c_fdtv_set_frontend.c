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
struct firedtv {int dummy; } ;
struct dtv_frontend_properties {int dummy; } ;
struct dvb_frontend {struct firedtv* sec_priv; struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
 int avc_tuner_dsd (struct firedtv*,struct dtv_frontend_properties*) ; 

__attribute__((used)) static int fdtv_set_frontend(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	struct firedtv *fdtv = fe->sec_priv;

	return avc_tuner_dsd(fdtv, p);
}