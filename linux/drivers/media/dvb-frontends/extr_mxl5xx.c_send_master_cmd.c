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
struct dvb_diseqc_master_cmd {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int send_master_cmd(struct dvb_frontend *fe,
			   struct dvb_diseqc_master_cmd *cmd)
{
	/*struct mxl *state = fe->demodulator_priv;*/

	return 0; /*CfgDemodAbortTune(state);*/
}