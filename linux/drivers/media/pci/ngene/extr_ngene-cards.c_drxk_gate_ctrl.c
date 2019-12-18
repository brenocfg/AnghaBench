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
struct ngene_channel {int (* gate_ctrl ) (struct dvb_frontend*,int) ;TYPE_1__* dev; } ;
struct dvb_frontend {struct ngene_channel* sec_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  pll_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int stub1 (struct dvb_frontend*,int) ; 
 int stub2 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drxk_gate_ctrl(struct dvb_frontend *fe, int enable)
{
	struct ngene_channel *chan = fe->sec_priv;
	int status;

	if (enable) {
		down(&chan->dev->pll_mutex);
		status = chan->gate_ctrl(fe, 1);
	} else {
		status = chan->gate_ctrl(fe, 0);
		up(&chan->dev->pll_mutex);
	}
	return status;
}