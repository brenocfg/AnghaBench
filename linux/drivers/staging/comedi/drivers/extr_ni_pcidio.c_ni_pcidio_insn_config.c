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
struct nidio_board {unsigned int dio_speed; } ;
struct comedi_subdevice {int /*<<< orphan*/  io_bits; } ;
struct comedi_insn {int n; } ;
struct comedi_device {scalar_t__ mmio; struct nidio_board* board_ptr; } ;

/* Variables and functions */
 unsigned int INSN_CONFIG_GET_CMD_TIMING_CONSTRAINTS ; 
 scalar_t__ PORT_PIN_DIRECTIONS (int /*<<< orphan*/ ) ; 
 int comedi_dio_insn_config (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ni_pcidio_insn_config(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn,
				 unsigned int *data)
{
	int ret;

	if (data[0] == INSN_CONFIG_GET_CMD_TIMING_CONSTRAINTS) {
		const struct nidio_board *board = dev->board_ptr;

		/* we don't care about actual channels */
		data[1] = board->dio_speed;
		data[2] = 0;
		return 0;
	}

	ret = comedi_dio_insn_config(dev, s, insn, data, 0);
	if (ret)
		return ret;

	writel(s->io_bits, dev->mmio + PORT_PIN_DIRECTIONS(0));

	return insn->n;
}