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
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 

__attribute__((used)) static int ttusbdecfe_dvbs_read_status(struct dvb_frontend *fe,
				       enum fe_status *status)
{
	*status = FE_HAS_SIGNAL | FE_HAS_VITERBI |
		FE_HAS_SYNC | FE_HAS_CARRIER | FE_HAS_LOCK;
	return 0;
}