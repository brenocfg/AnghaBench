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
struct pci_dev {unsigned int irq; } ;
struct nidio_board {scalar_t__ uses_firmware; int /*<<< orphan*/  name; } ;
struct nidio96_private {int /*<<< orphan*/  di_mite_ring; int /*<<< orphan*/  mite; int /*<<< orphan*/  mite_channel_lock; } ;
struct comedi_subdevice {int subdev_flags; int n_chan; int maxdata; int len_chanlist; int /*<<< orphan*/ * poll; int /*<<< orphan*/  async_dma_dir; int /*<<< orphan*/ * buf_change; int /*<<< orphan*/ * cancel; int /*<<< orphan*/ * do_cmdtest; int /*<<< orphan*/ * do_cmd; int /*<<< orphan*/ * insn_bits; int /*<<< orphan*/ * insn_config; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  type; } ;
struct comedi_device {unsigned int irq; int /*<<< orphan*/  board_name; struct comedi_subdevice* read_subdev; struct comedi_subdevice* subdevices; scalar_t__ mmio; int /*<<< orphan*/  class_dev; struct nidio_board const* board_ptr; } ;

/* Variables and functions */
 unsigned long ARRAY_SIZE (struct nidio_board*) ; 
 scalar_t__ CHIP_VERSION ; 
 int /*<<< orphan*/  COMEDI_SUBD_DIO ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int SDF_CMD_READ ; 
 int SDF_LSAMPL ; 
 int SDF_PACKED ; 
 int SDF_READABLE ; 
 int SDF_WRITABLE ; 
 struct nidio96_private* comedi_alloc_devpriv (struct comedi_device*,int) ; 
 int comedi_alloc_subdevices (struct comedi_device*,int) ; 
 int comedi_pci_enable (struct comedi_device*) ; 
 struct pci_dev* comedi_to_pci_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_alloc_ring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_attach (struct comedi_device*,int) ; 
 int /*<<< orphan*/  ni_pcidio_cancel ; 
 int /*<<< orphan*/  ni_pcidio_change ; 
 int /*<<< orphan*/  ni_pcidio_cmd ; 
 int /*<<< orphan*/  ni_pcidio_cmdtest ; 
 int /*<<< orphan*/  ni_pcidio_insn_bits ; 
 int /*<<< orphan*/  ni_pcidio_insn_config ; 
 int /*<<< orphan*/  ni_pcidio_poll ; 
 struct nidio_board* nidio_boards ; 
 int /*<<< orphan*/  nidio_interrupt ; 
 int /*<<< orphan*/  nidio_reset_board (struct comedi_device*) ; 
 int pci_6534_upload_firmware (struct comedi_device*) ; 
 int /*<<< orphan*/  range_digital ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int request_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comedi_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nidio_auto_attach(struct comedi_device *dev,
			     unsigned long context)
{
	struct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const struct nidio_board *board = NULL;
	struct nidio96_private *devpriv;
	struct comedi_subdevice *s;
	int ret;
	unsigned int irq;

	if (context < ARRAY_SIZE(nidio_boards))
		board = &nidio_boards[context];
	if (!board)
		return -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	ret = comedi_pci_enable(dev);
	if (ret)
		return ret;

	devpriv = comedi_alloc_devpriv(dev, sizeof(*devpriv));
	if (!devpriv)
		return -ENOMEM;

	spin_lock_init(&devpriv->mite_channel_lock);

	devpriv->mite = mite_attach(dev, false);	/* use win0 */
	if (!devpriv->mite)
		return -ENOMEM;

	devpriv->di_mite_ring = mite_alloc_ring(devpriv->mite);
	if (!devpriv->di_mite_ring)
		return -ENOMEM;

	if (board->uses_firmware) {
		ret = pci_6534_upload_firmware(dev);
		if (ret < 0)
			return ret;
	}

	nidio_reset_board(dev);

	ret = comedi_alloc_subdevices(dev, 1);
	if (ret)
		return ret;

	dev_info(dev->class_dev, "%s rev=%d\n", dev->board_name,
		 readb(dev->mmio + CHIP_VERSION));

	s = &dev->subdevices[0];

	dev->read_subdev = s;
	s->type = COMEDI_SUBD_DIO;
	s->subdev_flags =
		SDF_READABLE | SDF_WRITABLE | SDF_LSAMPL | SDF_PACKED |
		SDF_CMD_READ;
	s->n_chan = 32;
	s->range_table = &range_digital;
	s->maxdata = 1;
	s->insn_config = &ni_pcidio_insn_config;
	s->insn_bits = &ni_pcidio_insn_bits;
	s->do_cmd = &ni_pcidio_cmd;
	s->do_cmdtest = &ni_pcidio_cmdtest;
	s->cancel = &ni_pcidio_cancel;
	s->len_chanlist = 32;	/* XXX */
	s->buf_change = &ni_pcidio_change;
	s->async_dma_dir = DMA_BIDIRECTIONAL;
	s->poll = &ni_pcidio_poll;

	irq = pcidev->irq;
	if (irq) {
		ret = request_irq(irq, nidio_interrupt, IRQF_SHARED,
				  dev->board_name, dev);
		if (ret == 0)
			dev->irq = irq;
	}

	return 0;
}