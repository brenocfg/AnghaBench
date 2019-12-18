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
struct priv_pcm3724 {unsigned int dio_1; unsigned int dio_2; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ iobase; struct comedi_subdevice* subdevices; struct priv_pcm3724* private; } ;

/* Variables and functions */
 int CR_CHAN (int) ; 
 int PCM3724_GATE_CTRL_A0_ENA ; 
 int PCM3724_GATE_CTRL_A1_ENA ; 
 int PCM3724_GATE_CTRL_B0_ENA ; 
 int PCM3724_GATE_CTRL_B1_ENA ; 
 int PCM3724_GATE_CTRL_C0_ENA ; 
 int PCM3724_GATE_CTRL_C1_ENA ; 
 scalar_t__ PCM3724_GATE_CTRL_REG ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void enable_chan(struct comedi_device *dev, struct comedi_subdevice *s,
			int chanspec)
{
	struct priv_pcm3724 *priv = dev->private;
	struct comedi_subdevice *s_dio1 = &dev->subdevices[0];
	unsigned int mask;
	int gatecfg;

	gatecfg = 0;

	mask = 1 << CR_CHAN(chanspec);
	if (s == s_dio1)
		priv->dio_1 |= mask;
	else
		priv->dio_2 |= mask;

	if (priv->dio_1 & 0xff0000)
		gatecfg |= PCM3724_GATE_CTRL_C0_ENA;

	if (priv->dio_1 & 0xff00)
		gatecfg |= PCM3724_GATE_CTRL_B0_ENA;

	if (priv->dio_1 & 0xff)
		gatecfg |= PCM3724_GATE_CTRL_A0_ENA;

	if (priv->dio_2 & 0xff0000)
		gatecfg |= PCM3724_GATE_CTRL_C1_ENA;

	if (priv->dio_2 & 0xff00)
		gatecfg |= PCM3724_GATE_CTRL_B1_ENA;

	if (priv->dio_2 & 0xff)
		gatecfg |= PCM3724_GATE_CTRL_A1_ENA;

	outb(gatecfg, dev->iobase + PCM3724_GATE_CTRL_REG);
}