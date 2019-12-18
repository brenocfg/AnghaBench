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
typedef  int u16 ;
struct s626_private {scalar_t__ ai_convert_count; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {struct comedi_subdevice* read_subdev; struct s626_private* private; } ;
struct comedi_cmd {scalar_t__ convert_src; scalar_t__ scan_begin_src; scalar_t__ chanlist_len; } ;
struct comedi_async {struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  S626_CLKENAB_ALWAYS ; 
 int /*<<< orphan*/  S626_CLKENAB_INDEX ; 
 int S626_IRQ_COINT1A ; 
 int S626_IRQ_COINT1B ; 
 int S626_IRQ_COINT2A ; 
 int S626_IRQ_COINT2B ; 
 int S626_IRQ_COINT3A ; 
 int S626_IRQ_COINT3B ; 
 int /*<<< orphan*/  S626_LP_RDMISC2 ; 
 int /*<<< orphan*/  S626_MC2_ADC_RPS ; 
 int /*<<< orphan*/  S626_P_MC2 ; 
 scalar_t__ TRIG_TIMER ; 
 int s626_debi_read (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s626_mc_enable (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s626_reset_cap_flags (struct comedi_device*,int) ; 
 int /*<<< orphan*/  s626_set_enable (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s626_check_counter_interrupts(struct comedi_device *dev)
{
	struct s626_private *devpriv = dev->private;
	struct comedi_subdevice *s = dev->read_subdev;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	u16 irqbit;

	/* read interrupt type */
	irqbit = s626_debi_read(dev, S626_LP_RDMISC2);

	/* check interrupt on counters */
	if (irqbit & S626_IRQ_COINT1A) {
		/* clear interrupt capture flag */
		s626_reset_cap_flags(dev, 0);
	}
	if (irqbit & S626_IRQ_COINT2A) {
		/* clear interrupt capture flag */
		s626_reset_cap_flags(dev, 1);
	}
	if (irqbit & S626_IRQ_COINT3A) {
		/* clear interrupt capture flag */
		s626_reset_cap_flags(dev, 2);
	}
	if (irqbit & S626_IRQ_COINT1B) {
		/* clear interrupt capture flag */
		s626_reset_cap_flags(dev, 3);
	}
	if (irqbit & S626_IRQ_COINT2B) {
		/* clear interrupt capture flag */
		s626_reset_cap_flags(dev, 4);

		if (devpriv->ai_convert_count > 0) {
			devpriv->ai_convert_count--;
			if (devpriv->ai_convert_count == 0)
				s626_set_enable(dev, 4, S626_CLKENAB_INDEX);

			if (cmd->convert_src == TRIG_TIMER) {
				/* Trigger ADC scan loop start */
				s626_mc_enable(dev, S626_MC2_ADC_RPS,
					       S626_P_MC2);
			}
		}
	}
	if (irqbit & S626_IRQ_COINT3B) {
		/* clear interrupt capture flag */
		s626_reset_cap_flags(dev, 5);

		if (cmd->scan_begin_src == TRIG_TIMER) {
			/* Trigger ADC scan loop start */
			s626_mc_enable(dev, S626_MC2_ADC_RPS, S626_P_MC2);
		}

		if (cmd->convert_src == TRIG_TIMER) {
			devpriv->ai_convert_count = cmd->chanlist_len;
			s626_set_enable(dev, 4, S626_CLKENAB_ALWAYS);
		}
	}
}