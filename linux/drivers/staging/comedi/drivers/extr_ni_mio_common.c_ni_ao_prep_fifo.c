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
struct ni_private {scalar_t__ is_6xxx; } ;
struct ni_board_struct {unsigned int ao_fifo_depth; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct ni_private* private; struct ni_board_struct* board_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NI611X_AO_FIFO_OFFSET_LOAD_REG ; 
 int /*<<< orphan*/  NISTC_DAC_FIFO_CLR_REG ; 
 unsigned int comedi_buf_read_n_available (struct comedi_subdevice*) ; 
 unsigned int comedi_bytes_to_samples (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  ni_ao_fifo_load (struct comedi_device*,struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  ni_ao_win_outl (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_ao_prep_fifo(struct comedi_device *dev,
			   struct comedi_subdevice *s)
{
	const struct ni_board_struct *board = dev->board_ptr;
	struct ni_private *devpriv = dev->private;
	unsigned int nbytes;
	unsigned int nsamples;

	/* reset fifo */
	ni_stc_writew(dev, 1, NISTC_DAC_FIFO_CLR_REG);
	if (devpriv->is_6xxx)
		ni_ao_win_outl(dev, 0x6, NI611X_AO_FIFO_OFFSET_LOAD_REG);

	/* load some data */
	nbytes = comedi_buf_read_n_available(s);
	if (nbytes == 0)
		return 0;

	nsamples = comedi_bytes_to_samples(s, nbytes);
	if (nsamples > board->ao_fifo_depth)
		nsamples = board->ao_fifo_depth;

	ni_ao_fifo_load(dev, s, nsamples);

	return nsamples;
}