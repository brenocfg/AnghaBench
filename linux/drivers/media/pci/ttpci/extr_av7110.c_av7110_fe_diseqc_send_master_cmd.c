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
struct dvb_frontend {TYPE_1__* dvb; } ;
struct dvb_diseqc_master_cmd {int dummy; } ;
struct av7110 {int (* fe_diseqc_send_master_cmd ) (struct dvb_frontend*,struct dvb_diseqc_master_cmd*) ;struct dvb_diseqc_master_cmd saved_master_cmd; } ;
struct TYPE_2__ {struct av7110* priv; } ;

/* Variables and functions */
 int av7110_fe_lock_fix (struct av7110*,int /*<<< orphan*/ ) ; 
 int stub1 (struct dvb_frontend*,struct dvb_diseqc_master_cmd*) ; 

__attribute__((used)) static int av7110_fe_diseqc_send_master_cmd(struct dvb_frontend* fe,
					    struct dvb_diseqc_master_cmd* cmd)
{
	struct av7110* av7110 = fe->dvb->priv;

	int ret = av7110_fe_lock_fix(av7110, 0);
	if (!ret) {
		av7110->saved_master_cmd = *cmd;
		ret = av7110->fe_diseqc_send_master_cmd(fe, cmd);
	}
	return ret;
}