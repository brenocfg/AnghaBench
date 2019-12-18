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
struct ni_board_struct {scalar_t__ ao_fifo_depth; } ;
struct comedi_device {struct ni_board_struct* board_ptr; } ;
struct comedi_cmd {int dummy; } ;
struct TYPE_2__ {scalar_t__ is_m_series; } ;

/* Variables and functions */
 unsigned int NISTC_AO_PERSONAL_BC_SRC_SEL ; 
 unsigned int NISTC_AO_PERSONAL_DMA_PIO_CTRL ; 
 unsigned int NISTC_AO_PERSONAL_FIFO_ENA ; 
 unsigned int NISTC_AO_PERSONAL_NUM_DAC ; 
 int /*<<< orphan*/  NISTC_AO_PERSONAL_REG ; 
 unsigned int NISTC_AO_PERSONAL_TMRDACWR_PW ; 
 unsigned int NISTC_AO_PERSONAL_UPDATE_PW ; 
 unsigned int NISTC_RESET_AO_CFG_END ; 
 unsigned int NISTC_RESET_AO_CFG_START ; 
 int /*<<< orphan*/  NISTC_RESET_REG ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_ao_cmd_personalize(struct comedi_device *dev,
				  const struct comedi_cmd *cmd)
{
	const struct ni_board_struct *board = dev->board_ptr;
	unsigned int bits;

	ni_stc_writew(dev, NISTC_RESET_AO_CFG_START, NISTC_RESET_REG);

	bits =
	  /* fast CPU interface--only eseries */
	  /* ((slow CPU interface) ? 0 : AO_Fast_CPU) | */
	  NISTC_AO_PERSONAL_BC_SRC_SEL  |
	  0 /* (use_original_pulse ? 0 : NISTC_AO_PERSONAL_UPDATE_TIMEBASE) */ |
	  /*
	   * FIXME:  start setting following bit when appropriate.  Need to
	   * determine whether board is E4 or E1.
	   * FROM MHHDK:
	   * if board is E4 or E1
	   *   Set bit "NISTC_AO_PERSONAL_UPDATE_PW" to 0
	   * else
	   *   set it to 1
	   */
	  NISTC_AO_PERSONAL_UPDATE_PW   |
	  /* FIXME:  when should we set following bit to zero? */
	  NISTC_AO_PERSONAL_TMRDACWR_PW |
	  (board->ao_fifo_depth ?
	    NISTC_AO_PERSONAL_FIFO_ENA : NISTC_AO_PERSONAL_DMA_PIO_CTRL)
	  ;
#if 0
	/*
	 * FIXME:
	 * add something like ".has_individual_dacs = 0" to ni_board_struct
	 * since, as F Hess pointed out, not all in m series have singles.  not
	 * sure if e-series all have duals...
	 */

	/*
	 * F Hess: windows driver does not set NISTC_AO_PERSONAL_NUM_DAC bit for
	 * 6281, verified with bus analyzer.
	 */
	if (devpriv->is_m_series)
		bits |= NISTC_AO_PERSONAL_NUM_DAC;
#endif
	ni_stc_writew(dev, bits, NISTC_AO_PERSONAL_REG);

	ni_stc_writew(dev, NISTC_RESET_AO_CFG_END, NISTC_RESET_REG);
}