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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {TYPE_1__ ops; } ;

/* Variables and functions */
 int mxl5005s_writereg (struct dvb_frontend*,int,int,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int mxl5005s_writeregs(struct dvb_frontend *fe, u8 *addrtable,
	u8 *datatable, u8 len)
{
	int ret = 0, i;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	for (i = 0 ; i < len-1; i++) {
		ret = mxl5005s_writereg(fe, addrtable[i], datatable[i], 0);
		if (ret < 0)
			break;
	}

	ret = mxl5005s_writereg(fe, addrtable[i], datatable[i], 1);

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	return ret;
}