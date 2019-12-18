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
struct pci_dev {int dummy; } ;
struct comedi_subdevice {int n_chan; int maxdata; int /*<<< orphan*/  insn_write; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  subdev_flags; int /*<<< orphan*/  type; } ;
struct comedi_device {struct comedi_subdevice* subdevices; void* iobase; int /*<<< orphan*/  board_name; struct cb_pcidda_board const* board_ptr; } ;
struct cb_pcidda_private {int /*<<< orphan*/ * ao_range; int /*<<< orphan*/ * eeprom_data; void* daqio; } ;
struct cb_pcidda_board {int ao_chans; int ao_bits; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned long ARRAY_SIZE (struct cb_pcidda_board*) ; 
 int /*<<< orphan*/  COMEDI_SUBD_AO ; 
 int EEPROM_SIZE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int I8255_SIZE ; 
 int /*<<< orphan*/  SDF_WRITABLE ; 
 int /*<<< orphan*/  cb_pcidda_ao_insn_write ; 
 struct cb_pcidda_board* cb_pcidda_boards ; 
 int /*<<< orphan*/  cb_pcidda_calibrate (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb_pcidda_ranges ; 
 int /*<<< orphan*/  cb_pcidda_read_eeprom (struct comedi_device*,int) ; 
 struct cb_pcidda_private* comedi_alloc_devpriv (struct comedi_device*,int) ; 
 int comedi_alloc_subdevices (struct comedi_device*,int) ; 
 int comedi_pci_enable (struct comedi_device*) ; 
 struct pci_dev* comedi_to_pci_dev (struct comedi_device*) ; 
 void* pci_resource_start (struct pci_dev*,int) ; 
 int subdev_8255_init (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cb_pcidda_auto_attach(struct comedi_device *dev,
				 unsigned long context)
{
	struct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const struct cb_pcidda_board *board = NULL;
	struct cb_pcidda_private *devpriv;
	struct comedi_subdevice *s;
	int i;
	int ret;

	if (context < ARRAY_SIZE(cb_pcidda_boards))
		board = &cb_pcidda_boards[context];
	if (!board)
		return -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	devpriv = comedi_alloc_devpriv(dev, sizeof(*devpriv));
	if (!devpriv)
		return -ENOMEM;

	ret = comedi_pci_enable(dev);
	if (ret)
		return ret;
	dev->iobase = pci_resource_start(pcidev, 2);
	devpriv->daqio = pci_resource_start(pcidev, 3);

	ret = comedi_alloc_subdevices(dev, 3);
	if (ret)
		return ret;

	s = &dev->subdevices[0];
	/* analog output subdevice */
	s->type = COMEDI_SUBD_AO;
	s->subdev_flags = SDF_WRITABLE;
	s->n_chan = board->ao_chans;
	s->maxdata = (1 << board->ao_bits) - 1;
	s->range_table = &cb_pcidda_ranges;
	s->insn_write = cb_pcidda_ao_insn_write;

	/* two 8255 digital io subdevices */
	for (i = 0; i < 2; i++) {
		s = &dev->subdevices[1 + i];
		ret = subdev_8255_init(dev, s, NULL, i * I8255_SIZE);
		if (ret)
			return ret;
	}

	/* Read the caldac eeprom data */
	for (i = 0; i < EEPROM_SIZE; i++)
		devpriv->eeprom_data[i] = cb_pcidda_read_eeprom(dev, i);

	/*  set calibrations dacs */
	for (i = 0; i < board->ao_chans; i++)
		cb_pcidda_calibrate(dev, i, devpriv->ao_range[i]);

	return 0;
}