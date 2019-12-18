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
struct dvb_frontend {struct dib7000p_ops* sec_priv; } ;
struct dib7000p_ops {int (* set_gpio ) (struct dvb_frontend*,int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int stub1 (struct dvb_frontend*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dib7070_tuner_reset(struct dvb_frontend *fe, int onoff)
{
	struct dib7000p_ops *dib7000p_ops = fe->sec_priv;

	return dib7000p_ops->set_gpio(fe, 8, 0, !onoff);
}