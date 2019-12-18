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
struct ni_private {int /*<<< orphan*/  cdo_mite_ring; int /*<<< orphan*/  routing_tables; } ;
struct comedi_subdevice {int io_bits; unsigned int state; TYPE_1__* async; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct ni_private* private; } ;
struct comedi_cmd {int scan_begin_arg; } ;
struct TYPE_2__ {int prealloc_bufsz; int /*<<< orphan*/  inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_CHAN (int) ; 
 int CR_INVERT ; 
 int EIO ; 
 int /*<<< orphan*/  NI_DO_SampleClock ; 
 int /*<<< orphan*/  NI_M_CDIO_CMD_REG ; 
 unsigned int NI_M_CDO_CMD_RESET ; 
 unsigned int NI_M_CDO_CMD_SW_UPDATE ; 
 int /*<<< orphan*/  NI_M_CDO_FIFO_DATA_REG ; 
 int /*<<< orphan*/  NI_M_CDO_MASK_ENA_REG ; 
 unsigned int NI_M_CDO_MODE_FIFO_MODE ; 
 unsigned int NI_M_CDO_MODE_HALT_ON_ERROR ; 
 unsigned int NI_M_CDO_MODE_POLARITY ; 
 int /*<<< orphan*/  NI_M_CDO_MODE_REG ; 
 unsigned int NI_M_CDO_MODE_SAMPLE_SRC (int /*<<< orphan*/ ) ; 
 int comedi_bytes_per_scan (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ni_cdo_inttrig ; 
 int /*<<< orphan*/  ni_cmd_set_mite_transfer (int /*<<< orphan*/ ,struct comedi_subdevice*,struct comedi_cmd const*,int) ; 
 int /*<<< orphan*/  ni_get_reg_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ni_request_cdo_mite_channel (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_writel (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_cdio_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct ni_private *devpriv = dev->private;
	const struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int cdo_mode_bits;
	int retval;

	ni_writel(dev, NI_M_CDO_CMD_RESET, NI_M_CDIO_CMD_REG);
	/*
	 * Although NI_D[IO]_SampleClock are the same, perhaps we should still,
	 * for completeness, test whether the cmd is output or input(?)
	 */
	cdo_mode_bits = NI_M_CDO_MODE_FIFO_MODE |
			NI_M_CDO_MODE_HALT_ON_ERROR |
			NI_M_CDO_MODE_SAMPLE_SRC(
				ni_get_reg_value(CR_CHAN(cmd->scan_begin_arg),
						 NI_DO_SampleClock,
						 &devpriv->routing_tables));
	if (cmd->scan_begin_arg & CR_INVERT)
		cdo_mode_bits |= NI_M_CDO_MODE_POLARITY;
	ni_writel(dev, cdo_mode_bits, NI_M_CDO_MODE_REG);
	if (s->io_bits) {
		ni_writel(dev, s->state, NI_M_CDO_FIFO_DATA_REG);
		ni_writel(dev, NI_M_CDO_CMD_SW_UPDATE, NI_M_CDIO_CMD_REG);
		ni_writel(dev, s->io_bits, NI_M_CDO_MASK_ENA_REG);
	} else {
		dev_err(dev->class_dev,
			"attempted to run digital output command with no lines configured as outputs\n");
		return -EIO;
	}
	retval = ni_request_cdo_mite_channel(dev);
	if (retval < 0)
		return retval;

	ni_cmd_set_mite_transfer(devpriv->cdo_mite_ring, s, cmd,
				 s->async->prealloc_bufsz /
				 comedi_bytes_per_scan(s));

	s->async->inttrig = ni_cdo_inttrig;

	return 0;
}