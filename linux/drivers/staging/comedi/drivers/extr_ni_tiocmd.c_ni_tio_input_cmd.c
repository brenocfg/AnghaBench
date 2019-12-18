#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ni_route_tables {int dummy; } ;
struct ni_gpct_device {int variant; struct ni_route_tables* routing_tables; } ;
struct ni_gpct {unsigned int counter_index; TYPE_1__* mite_chan; struct ni_gpct_device* counter_dev; } ;
struct comedi_subdevice {struct comedi_async* async; struct ni_gpct* private; } ;
struct comedi_cmd {scalar_t__ start_src; int /*<<< orphan*/  start_arg; } ;
struct comedi_async {int /*<<< orphan*/ * inttrig; int /*<<< orphan*/  prealloc_bufsz; struct comedi_cmd cmd; } ;
struct TYPE_3__ {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_INPUT ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GI_SAVE_TRACE ; 
 int /*<<< orphan*/  NITIO_CMD_REG (unsigned int) ; 
 int /*<<< orphan*/  NI_CtrArmStartTrigger (unsigned int) ; 
 int NI_GPCT_ARM_IMMEDIATE ; 
 int NI_GPCT_HW_ARM ; 
 int NI_NAMES_BASE ; 
 scalar_t__ TRIG_EXT ; 
 scalar_t__ TRIG_INT ; 
 scalar_t__ TRIG_NOW ; 
 int /*<<< orphan*/  comedi_buf_write_alloc (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_dma_arm (TYPE_1__*) ; 
 int /*<<< orphan*/  mite_prep_dma (TYPE_1__*,int,int) ; 
 int ni_get_reg_value (int,int /*<<< orphan*/ ,struct ni_route_tables const*) ; 
#define  ni_gpct_variant_660x 130 
#define  ni_gpct_variant_e_series 129 
#define  ni_gpct_variant_m_series 128 
 int ni_tio_arm (struct ni_gpct*,int,int) ; 
 int /*<<< orphan*/  ni_tio_configure_dma (struct ni_gpct*,int,int) ; 
 int /*<<< orphan*/  ni_tio_input_inttrig ; 
 int /*<<< orphan*/  ni_tio_set_bits (struct ni_gpct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_tio_input_cmd(struct comedi_subdevice *s)
{
	struct ni_gpct *counter = s->private;
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	const struct ni_route_tables *routing_tables =
		counter_dev->routing_tables;
	unsigned int cidx = counter->counter_index;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	int ret = 0;

	/* write alloc the entire buffer */
	comedi_buf_write_alloc(s, async->prealloc_bufsz);
	counter->mite_chan->dir = COMEDI_INPUT;
	switch (counter_dev->variant) {
	case ni_gpct_variant_m_series:
	case ni_gpct_variant_660x:
		mite_prep_dma(counter->mite_chan, 32, 32);
		break;
	case ni_gpct_variant_e_series:
		mite_prep_dma(counter->mite_chan, 16, 32);
		break;
	}
	ni_tio_set_bits(counter, NITIO_CMD_REG(cidx), GI_SAVE_TRACE, 0);
	ni_tio_configure_dma(counter, true, true);

	if (cmd->start_src == TRIG_INT) {
		async->inttrig = &ni_tio_input_inttrig;
	} else {	/* TRIG_NOW || TRIG_EXT || TRIG_OTHER */
		async->inttrig = NULL;
		mite_dma_arm(counter->mite_chan);

		if (cmd->start_src == TRIG_NOW)
			ret = ni_tio_arm(counter, true, NI_GPCT_ARM_IMMEDIATE);
		else if (cmd->start_src == TRIG_EXT) {
			int reg = CR_CHAN(cmd->start_arg);

			if (reg >= NI_NAMES_BASE) {
				/* using a device-global name. lookup reg */
				reg = ni_get_reg_value(reg,
						       NI_CtrArmStartTrigger(cidx),
						       routing_tables);
				/* mark this as a raw register value */
				reg |= NI_GPCT_HW_ARM;
			}
			ret = ni_tio_arm(counter, true, reg);
		}
	}
	return ret;
}