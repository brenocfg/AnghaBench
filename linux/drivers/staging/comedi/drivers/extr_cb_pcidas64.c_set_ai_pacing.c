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
typedef  int u32 ;
struct pcidas64_private {scalar_t__ main_iobase; } ;
struct pcidas64_board {scalar_t__ layout; } ;
struct comedi_device {struct pcidas64_private* private; struct pcidas64_board* board_ptr; } ;
struct comedi_cmd {int dummy; } ;

/* Variables and functions */
 scalar_t__ ADC_DELAY_INTERVAL_LOWER_REG ; 
 scalar_t__ ADC_DELAY_INTERVAL_UPPER_REG ; 
 scalar_t__ ADC_SAMPLE_INTERVAL_LOWER_REG ; 
 scalar_t__ ADC_SAMPLE_INTERVAL_UPPER_REG ; 
 scalar_t__ LAYOUT_4020 ; 
 int ai_convert_counter_4020 (struct comedi_device*,struct comedi_cmd*) ; 
 int ai_convert_counter_6xxx (struct comedi_device*,struct comedi_cmd*) ; 
 int ai_scan_counter_6xxx (struct comedi_device*,struct comedi_cmd*) ; 
 int /*<<< orphan*/  check_adc_timing (struct comedi_device*,struct comedi_cmd*) ; 
 int /*<<< orphan*/  select_master_clock (struct comedi_device*,struct comedi_cmd*) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void set_ai_pacing(struct comedi_device *dev, struct comedi_cmd *cmd)
{
	const struct pcidas64_board *board = dev->board_ptr;
	struct pcidas64_private *devpriv = dev->private;
	u32 convert_counter = 0, scan_counter = 0;

	check_adc_timing(dev, cmd);

	select_master_clock(dev, cmd);

	if (board->layout == LAYOUT_4020) {
		convert_counter = ai_convert_counter_4020(dev, cmd);
	} else {
		convert_counter = ai_convert_counter_6xxx(dev, cmd);
		scan_counter = ai_scan_counter_6xxx(dev, cmd);
	}

	/* load lower 16 bits of convert interval */
	writew(convert_counter & 0xffff,
	       devpriv->main_iobase + ADC_SAMPLE_INTERVAL_LOWER_REG);
	/* load upper 8 bits of convert interval */
	writew((convert_counter >> 16) & 0xff,
	       devpriv->main_iobase + ADC_SAMPLE_INTERVAL_UPPER_REG);
	/* load lower 16 bits of scan delay */
	writew(scan_counter & 0xffff,
	       devpriv->main_iobase + ADC_DELAY_INTERVAL_LOWER_REG);
	/* load upper 8 bits of scan delay */
	writew((scan_counter >> 16) & 0xff,
	       devpriv->main_iobase + ADC_DELAY_INTERVAL_UPPER_REG);
}