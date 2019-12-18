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
struct comedi_subdevice {unsigned int maxdata; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {struct apci1500_private* private; } ;
struct apci1500_private {unsigned int clk_src; scalar_t__ addon; } ;

/* Variables and functions */
 scalar_t__ APCI1500_CLK_SEL_REG ; 
 unsigned int COMEDI_COUNTER_ARMED ; 
 unsigned int COMEDI_COUNTER_COUNTING ; 
 unsigned int COMEDI_COUNTER_TERMINAL_COUNT ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  I8254_MODE0 141 
#define  I8254_MODE1 140 
#define  I8254_MODE2 139 
#define  I8254_MODE3 138 
#define  I8254_MODE4 137 
#define  I8254_MODE5 136 
#define  INSN_CONFIG_ARM 135 
#define  INSN_CONFIG_DISARM 134 
#define  INSN_CONFIG_GET_CLOCK_SRC 133 
#define  INSN_CONFIG_GET_COUNTER_STATUS 132 
#define  INSN_CONFIG_GET_GATE_SRC 131 
#define  INSN_CONFIG_SET_CLOCK_SRC 130 
#define  INSN_CONFIG_SET_COUNTER_MODE 129 
#define  INSN_CONFIG_SET_GATE_SRC 128 
 unsigned int Z8536_CT_CMDSTAT_GCB ; 
 int /*<<< orphan*/  Z8536_CT_CMDSTAT_REG (unsigned int) ; 
 unsigned int Z8536_CT_MODE_CSC ; 
 unsigned int Z8536_CT_MODE_DCS_ONESHOT ; 
 unsigned int Z8536_CT_MODE_DCS_PULSE ; 
 unsigned int Z8536_CT_MODE_DCS_SQRWAVE ; 
 unsigned int Z8536_CT_MODE_ECE ; 
 unsigned int Z8536_CT_MODE_EGE ; 
 unsigned int Z8536_CT_MODE_EOE ; 
 unsigned int Z8536_CT_MODE_ETE ; 
 unsigned int Z8536_CT_MODE_REB ; 
 int /*<<< orphan*/  Z8536_CT_MODE_REG (unsigned int) ; 
 int /*<<< orphan*/  Z8536_CT_RELOAD_LSB_REG (unsigned int) ; 
 int /*<<< orphan*/  Z8536_CT_RELOAD_MSB_REG (unsigned int) ; 
 unsigned int Z8536_CT_STAT_CIP ; 
 unsigned int Z8536_STAT_IP ; 
 int /*<<< orphan*/  apci1500_ack_irq (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apci1500_timer_enable (struct comedi_device*,unsigned int,int) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 unsigned int z8536_read (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  z8536_write (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apci1500_timer_insn_config(struct comedi_device *dev,
				      struct comedi_subdevice *s,
				      struct comedi_insn *insn,
				      unsigned int *data)
{
	struct apci1500_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int val;

	switch (data[0]) {
	case INSN_CONFIG_ARM:
		val = data[1] & s->maxdata;
		z8536_write(dev, val & 0xff, Z8536_CT_RELOAD_LSB_REG(chan));
		z8536_write(dev, (val >> 8) & 0xff,
			    Z8536_CT_RELOAD_MSB_REG(chan));

		apci1500_timer_enable(dev, chan, true);
		z8536_write(dev, Z8536_CT_CMDSTAT_GCB,
			    Z8536_CT_CMDSTAT_REG(chan));
		break;
	case INSN_CONFIG_DISARM:
		apci1500_timer_enable(dev, chan, false);
		break;

	case INSN_CONFIG_GET_COUNTER_STATUS:
		data[1] = 0;
		val = z8536_read(dev, Z8536_CT_CMDSTAT_REG(chan));
		if (val & Z8536_CT_STAT_CIP)
			data[1] |= COMEDI_COUNTER_COUNTING;
		if (val & Z8536_CT_CMDSTAT_GCB)
			data[1] |= COMEDI_COUNTER_ARMED;
		if (val & Z8536_STAT_IP) {
			data[1] |= COMEDI_COUNTER_TERMINAL_COUNT;
			apci1500_ack_irq(dev, Z8536_CT_CMDSTAT_REG(chan));
		}
		data[2] = COMEDI_COUNTER_ARMED | COMEDI_COUNTER_COUNTING |
			  COMEDI_COUNTER_TERMINAL_COUNT;
		break;

	case INSN_CONFIG_SET_COUNTER_MODE:
		/* Simulate the 8254 timer modes */
		switch (data[1]) {
		case I8254_MODE0:
			/* Interrupt on Terminal Count */
			val = Z8536_CT_MODE_ECE |
			      Z8536_CT_MODE_DCS_ONESHOT;
			break;
		case I8254_MODE1:
			/* Hardware Retriggerable One-Shot */
			val = Z8536_CT_MODE_ETE |
			      Z8536_CT_MODE_DCS_ONESHOT;
			break;
		case I8254_MODE2:
			/* Rate Generator */
			val = Z8536_CT_MODE_CSC |
			      Z8536_CT_MODE_DCS_PULSE;
			break;
		case I8254_MODE3:
			/* Square Wave Mode */
			val = Z8536_CT_MODE_CSC |
			      Z8536_CT_MODE_DCS_SQRWAVE;
			break;
		case I8254_MODE4:
			/* Software Triggered Strobe */
			val = Z8536_CT_MODE_REB |
			      Z8536_CT_MODE_DCS_PULSE;
			break;
		case I8254_MODE5:
			/* Hardware Triggered Strobe (watchdog) */
			val = Z8536_CT_MODE_EOE |
			      Z8536_CT_MODE_ETE |
			      Z8536_CT_MODE_REB |
			      Z8536_CT_MODE_DCS_PULSE;
			break;
		default:
			return -EINVAL;
		}
		apci1500_timer_enable(dev, chan, false);
		z8536_write(dev, val, Z8536_CT_MODE_REG(chan));
		break;

	case INSN_CONFIG_SET_CLOCK_SRC:
		if (data[1] > 2)
			return -EINVAL;
		devpriv->clk_src = data[1];
		if (devpriv->clk_src == 2)
			devpriv->clk_src = 3;
		outw(devpriv->clk_src, devpriv->addon + APCI1500_CLK_SEL_REG);
		break;
	case INSN_CONFIG_GET_CLOCK_SRC:
		switch (devpriv->clk_src) {
		case 0:
			data[1] = 0;		/* 111.86 kHz / 2 */
			data[2] = 17879;	/* 17879 ns (approx) */
			break;
		case 1:
			data[1] = 1;		/* 3.49 kHz / 2 */
			data[2] = 573066;	/* 573066 ns (approx) */
			break;
		case 3:
			data[1] = 2;		/* 1.747 kHz / 2 */
			data[2] = 1164822;	/* 1164822 ns (approx) */
			break;
		default:
			return -EINVAL;
		}
		break;

	case INSN_CONFIG_SET_GATE_SRC:
		if (chan == 0)
			return -EINVAL;

		val = z8536_read(dev, Z8536_CT_MODE_REG(chan));
		val &= Z8536_CT_MODE_EGE;
		if (data[1] == 1)
			val |= Z8536_CT_MODE_EGE;
		else if (data[1] > 1)
			return -EINVAL;
		z8536_write(dev, val, Z8536_CT_MODE_REG(chan));
		break;
	case INSN_CONFIG_GET_GATE_SRC:
		if (chan == 0)
			return -EINVAL;
		break;

	default:
		return -EINVAL;
	}
	return insn->n;
}