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
struct dvb_frontend {struct firedtv* sec_priv; } ;
struct dvb_diseqc_master_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LNBCONTROL_DONTCARE ; 
 int avc_lnb_control (struct firedtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct dvb_diseqc_master_cmd*) ; 

__attribute__((used)) static int fdtv_diseqc_send_master_cmd(struct dvb_frontend *fe,
				       struct dvb_diseqc_master_cmd *cmd)
{
	struct firedtv *fdtv = fe->sec_priv;

	return avc_lnb_control(fdtv, LNBCONTROL_DONTCARE, LNBCONTROL_DONTCARE,
			       LNBCONTROL_DONTCARE, 1, cmd);
}