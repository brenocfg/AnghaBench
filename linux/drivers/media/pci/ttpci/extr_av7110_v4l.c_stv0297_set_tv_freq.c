#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct saa7146_dev {scalar_t__ ext_priv; } ;
struct av7110 {TYPE_2__* fe; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (TYPE_2__*,int) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 
 int tuner_write (struct saa7146_dev*,int,int*) ; 

__attribute__((used)) static int stv0297_set_tv_freq(struct saa7146_dev *dev, u32 freq)
{
	struct av7110 *av7110 = (struct av7110*)dev->ext_priv;
	u32 div;
	u8 data[4];

	div = (freq + 38900000 + 31250) / 62500;

	data[0] = (div >> 8) & 0x7f;
	data[1] = div & 0xff;
	data[2] = 0xce;

	if (freq < 45000000)
		return -EINVAL;
	else if (freq < 137000000)
		data[3] = 0x01;
	else if (freq < 403000000)
		data[3] = 0x02;
	else if (freq < 860000000)
		data[3] = 0x04;
	else
		return -EINVAL;

	if (av7110->fe->ops.i2c_gate_ctrl)
		av7110->fe->ops.i2c_gate_ctrl(av7110->fe, 1);
	return tuner_write(dev, 0x63, data);
}