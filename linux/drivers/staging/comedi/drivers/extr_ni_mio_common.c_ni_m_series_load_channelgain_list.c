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
struct ni_private {unsigned int ai_calib_source; scalar_t__* ai_offset; } ;
struct ni_board_struct {size_t gainlkup; } ;
struct comedi_device {struct ni_private* private; struct ni_board_struct* board_ptr; } ;

/* Variables and functions */
#define  AREF_COMMON 131 
#define  AREF_DIFF 130 
#define  AREF_GROUND 129 
#define  AREF_OTHER 128 
 unsigned int CR_ALT_FILTER ; 
 unsigned int CR_ALT_SOURCE ; 
 unsigned int CR_AREF (unsigned int) ; 
 unsigned int CR_CHAN (unsigned int) ; 
 unsigned int CR_RANGE (unsigned int) ; 
 int /*<<< orphan*/  NISTC_CFG_MEM_CLR_REG ; 
 unsigned int NI_M_AI_CFG_BANK_SEL (unsigned int) ; 
 unsigned int NI_M_AI_CFG_CHAN_SEL (unsigned int) ; 
 unsigned int NI_M_AI_CFG_CHAN_TYPE_COMMON ; 
 unsigned int NI_M_AI_CFG_CHAN_TYPE_DIFF ; 
 unsigned int NI_M_AI_CFG_CHAN_TYPE_GROUND ; 
 unsigned int NI_M_AI_CFG_DITHER ; 
 int /*<<< orphan*/  NI_M_AI_CFG_FIFO_DATA_REG ; 
 unsigned int NI_M_AI_CFG_GAIN (unsigned int) ; 
 unsigned int NI_M_AI_CFG_LAST_CHAN ; 
 unsigned int NI_M_AI_CFG_POLARITY ; 
 unsigned int NI_M_CFG_BYPASS_AI_CHAN (unsigned int) ; 
 unsigned int NI_M_CFG_BYPASS_AI_DITHER ; 
 unsigned int NI_M_CFG_BYPASS_AI_GAIN (unsigned int) ; 
 unsigned int NI_M_CFG_BYPASS_AI_POLARITY ; 
 unsigned int NI_M_CFG_BYPASS_FIFO ; 
 int /*<<< orphan*/  NI_M_CFG_BYPASS_FIFO_REG ; 
 unsigned int** ni_gainlkup ; 
 int /*<<< orphan*/  ni_prime_channelgain_list (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_writel (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_writew (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_m_series_load_channelgain_list(struct comedi_device *dev,
					      unsigned int n_chan,
					      unsigned int *list)
{
	const struct ni_board_struct *board = dev->board_ptr;
	struct ni_private *devpriv = dev->private;
	unsigned int chan, range, aref;
	unsigned int i;
	unsigned int dither;
	unsigned int range_code;

	ni_stc_writew(dev, 1, NISTC_CFG_MEM_CLR_REG);

	if ((list[0] & CR_ALT_SOURCE)) {
		unsigned int bypass_bits;

		chan = CR_CHAN(list[0]);
		range = CR_RANGE(list[0]);
		range_code = ni_gainlkup[board->gainlkup][range];
		dither = (list[0] & CR_ALT_FILTER) != 0;
		bypass_bits = NI_M_CFG_BYPASS_FIFO |
			      NI_M_CFG_BYPASS_AI_CHAN(chan) |
			      NI_M_CFG_BYPASS_AI_GAIN(range_code) |
			      devpriv->ai_calib_source;
		if (dither)
			bypass_bits |= NI_M_CFG_BYPASS_AI_DITHER;
		/*  don't use 2's complement encoding */
		bypass_bits |= NI_M_CFG_BYPASS_AI_POLARITY;
		ni_writel(dev, bypass_bits, NI_M_CFG_BYPASS_FIFO_REG);
	} else {
		ni_writel(dev, 0, NI_M_CFG_BYPASS_FIFO_REG);
	}
	for (i = 0; i < n_chan; i++) {
		unsigned int config_bits = 0;

		chan = CR_CHAN(list[i]);
		aref = CR_AREF(list[i]);
		range = CR_RANGE(list[i]);
		dither = (list[i] & CR_ALT_FILTER) != 0;

		range_code = ni_gainlkup[board->gainlkup][range];
		devpriv->ai_offset[i] = 0;
		switch (aref) {
		case AREF_DIFF:
			config_bits |= NI_M_AI_CFG_CHAN_TYPE_DIFF;
			break;
		case AREF_COMMON:
			config_bits |= NI_M_AI_CFG_CHAN_TYPE_COMMON;
			break;
		case AREF_GROUND:
			config_bits |= NI_M_AI_CFG_CHAN_TYPE_GROUND;
			break;
		case AREF_OTHER:
			break;
		}
		config_bits |= NI_M_AI_CFG_CHAN_SEL(chan);
		config_bits |= NI_M_AI_CFG_BANK_SEL(chan);
		config_bits |= NI_M_AI_CFG_GAIN(range_code);
		if (i == n_chan - 1)
			config_bits |= NI_M_AI_CFG_LAST_CHAN;
		if (dither)
			config_bits |= NI_M_AI_CFG_DITHER;
		/*  don't use 2's complement encoding */
		config_bits |= NI_M_AI_CFG_POLARITY;
		ni_writew(dev, config_bits, NI_M_AI_CFG_FIFO_DATA_REG);
	}
	ni_prime_channelgain_list(dev);
}