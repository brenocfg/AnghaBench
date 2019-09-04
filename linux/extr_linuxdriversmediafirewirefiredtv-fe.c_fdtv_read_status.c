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
struct firedtv_tuner_status {scalar_t__ no_rf; } ;
struct firedtv {int dummy; } ;
struct dvb_frontend {struct firedtv* sec_priv; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int EINVAL ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 scalar_t__ avc_tuner_status (struct firedtv*,struct firedtv_tuner_status*) ; 

__attribute__((used)) static int fdtv_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct firedtv *fdtv = fe->sec_priv;
	struct firedtv_tuner_status stat;

	if (avc_tuner_status(fdtv, &stat))
		return -EINVAL;

	if (stat.no_rf)
		*status = 0;
	else
		*status = FE_HAS_SIGNAL | FE_HAS_VITERBI | FE_HAS_SYNC |
			  FE_HAS_CARRIER | FE_HAS_LOCK;
	return 0;
}