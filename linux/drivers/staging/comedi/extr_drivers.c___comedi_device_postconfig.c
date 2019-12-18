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
struct comedi_subdevice {scalar_t__ type; int n_chan; int io_bits; int len_chanlist; scalar_t__ poll; void* insn_config; void* insn_bits; void* insn_write; void* insn_read; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  range_table_list; scalar_t__ do_cmd; } ;
struct comedi_device {int n_subdevices; struct comedi_subdevice* subdevices; scalar_t__ get_valid_routes; scalar_t__ insn_device_config; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 scalar_t__ COMEDI_SUBD_DO ; 
 scalar_t__ COMEDI_SUBD_UNUSED ; 
 int __comedi_device_postconfig_async (struct comedi_device*,struct comedi_subdevice*) ; 
 scalar_t__ get_zero_valid_routes ; 
 scalar_t__ insn_device_inval ; 
 void* insn_inval ; 
 void* insn_rw_emulate_bits ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ poll_invalid ; 
 int /*<<< orphan*/  range_unknown ; 

__attribute__((used)) static int __comedi_device_postconfig(struct comedi_device *dev)
{
	struct comedi_subdevice *s;
	int ret;
	int i;

	lockdep_assert_held(&dev->mutex);
	if (!dev->insn_device_config)
		dev->insn_device_config = insn_device_inval;

	if (!dev->get_valid_routes)
		dev->get_valid_routes = get_zero_valid_routes;

	for (i = 0; i < dev->n_subdevices; i++) {
		s = &dev->subdevices[i];

		if (s->type == COMEDI_SUBD_UNUSED)
			continue;

		if (s->type == COMEDI_SUBD_DO) {
			if (s->n_chan < 32)
				s->io_bits = (1 << s->n_chan) - 1;
			else
				s->io_bits = 0xffffffff;
		}

		if (s->len_chanlist == 0)
			s->len_chanlist = 1;

		if (s->do_cmd) {
			ret = __comedi_device_postconfig_async(dev, s);
			if (ret)
				return ret;
		}

		if (!s->range_table && !s->range_table_list)
			s->range_table = &range_unknown;

		if (!s->insn_read && s->insn_bits)
			s->insn_read = insn_rw_emulate_bits;
		if (!s->insn_write && s->insn_bits)
			s->insn_write = insn_rw_emulate_bits;

		if (!s->insn_read)
			s->insn_read = insn_inval;
		if (!s->insn_write)
			s->insn_write = insn_inval;
		if (!s->insn_bits)
			s->insn_bits = insn_inval;
		if (!s->insn_config)
			s->insn_config = insn_inval;

		if (!s->poll)
			s->poll = poll_invalid;
	}

	return 0;
}