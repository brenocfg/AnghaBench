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
struct em28xx_dvb {int (* gate_ctrl ) (struct dvb_frontend*,int) ;int /*<<< orphan*/  pll_mutex; } ;
struct dvb_frontend {struct em28xx_dvb* sec_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int stub1 (struct dvb_frontend*,int) ; 
 int stub2 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drxk_gate_ctrl(struct dvb_frontend *fe, int enable)
{
	struct em28xx_dvb *dvb = fe->sec_priv;
	int status;

	if (!dvb)
		return -EINVAL;

	if (enable) {
		down(&dvb->pll_mutex);
		status = dvb->gate_ctrl(fe, 1);
	} else {
		status = dvb->gate_ctrl(fe, 0);
		up(&dvb->pll_mutex);
	}
	return status;
}