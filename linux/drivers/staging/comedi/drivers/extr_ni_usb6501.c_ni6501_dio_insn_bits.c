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
typedef  int u8 ;
struct comedi_subdevice {int state; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_PORT ; 
 int /*<<< orphan*/  WRITE_PORT ; 
 unsigned int comedi_dio_update_state (struct comedi_subdevice*,unsigned int*) ; 
 int ni6501_port_command (struct comedi_device*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int ni6501_dio_insn_bits(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	unsigned int mask;
	int ret;
	u8 port;
	u8 bitmap;

	mask = comedi_dio_update_state(s, data);

	for (port = 0; port < 3; port++) {
		if (mask & (0xFF << port * 8)) {
			bitmap = (s->state >> port * 8) & 0xFF;
			ret = ni6501_port_command(dev, WRITE_PORT,
						  port, &bitmap);
			if (ret)
				return ret;
		}
	}

	data[1] = 0;

	for (port = 0; port < 3; port++) {
		ret = ni6501_port_command(dev, READ_PORT, port, &bitmap);
		if (ret)
			return ret;
		data[1] |= bitmap << port * 8;
	}

	return insn->n;
}