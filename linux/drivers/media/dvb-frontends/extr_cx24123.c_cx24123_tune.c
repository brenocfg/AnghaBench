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
 unsigned int FE_TUNE_MODE_ONESHOT ; 
 int HZ ; 
 int /*<<< orphan*/  cx24123_read_status (struct dvb_frontend*,int*) ; 
 int cx24123_set_frontend (struct dvb_frontend*) ; 

__attribute__((used)) static int cx24123_tune(struct dvb_frontend *fe,
			bool re_tune,
			unsigned int mode_flags,
			unsigned int *delay,
			enum fe_status *status)
{
	int retval = 0;

	if (re_tune)
		retval = cx24123_set_frontend(fe);

	if (!(mode_flags & FE_TUNE_MODE_ONESHOT))
		cx24123_read_status(fe, status);
	*delay = HZ/10;

	return retval;
}