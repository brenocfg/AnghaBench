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
struct dvb_frontend {int dummy; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int EINVAL ; 
 int HZ ; 
 int cxd2880_read_status (struct dvb_frontend*,int*) ; 
 int cxd2880_set_frontend (struct dvb_frontend*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int cxd2880_tune(struct dvb_frontend *fe,
			bool retune,
			unsigned int mode_flags,
			unsigned int *delay,
			enum fe_status *status)
{
	int ret;

	if (!fe || !delay || !status) {
		pr_err("invalid arg.");
		return -EINVAL;
	}

	if (retune) {
		ret = cxd2880_set_frontend(fe);
		if (ret) {
			pr_err("cxd2880_set_frontend failed %d\n", ret);
			return ret;
		}
	}

	*delay = HZ / 5;

	return cxd2880_read_status(fe, status);
}