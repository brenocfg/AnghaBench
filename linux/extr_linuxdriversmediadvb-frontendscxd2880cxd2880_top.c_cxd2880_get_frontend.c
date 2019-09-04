#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int delivery_system; } ;
struct dvb_frontend {TYPE_1__ dtv_property_cache; } ;
struct dtv_frontend_properties {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SYS_DVBT 129 
#define  SYS_DVBT2 128 
 int cxd2880_get_frontend_t (struct dvb_frontend*,struct dtv_frontend_properties*) ; 
 int cxd2880_get_frontend_t2 (struct dvb_frontend*,struct dtv_frontend_properties*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int cxd2880_get_frontend(struct dvb_frontend *fe,
				struct dtv_frontend_properties *props)
{
	int ret;

	if (!fe || !props) {
		pr_err("invalid arg.");
		return -EINVAL;
	}

	pr_debug("system=%d\n", fe->dtv_property_cache.delivery_system);
	switch (fe->dtv_property_cache.delivery_system) {
	case SYS_DVBT:
		ret = cxd2880_get_frontend_t(fe, props);
		break;
	case SYS_DVBT2:
		ret = cxd2880_get_frontend_t2(fe, props);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}