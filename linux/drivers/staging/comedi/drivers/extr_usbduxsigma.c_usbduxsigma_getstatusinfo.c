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
typedef  int u8 ;
typedef  int u32 ;
struct usbduxsigma_private {int* dux_commands; scalar_t__ insn_buf; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct usbduxsigma_private* private; struct comedi_subdevice* read_subdev; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  USBDUXSIGMA_SINGLE_AD_CMD ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ comedi_offset_munge (struct comedi_subdevice*,int) ; 
 int /*<<< orphan*/  get_unaligned (int /*<<< orphan*/ *) ; 
 int usbbuxsigma_send_cmd (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int usbduxsigma_receive_cmd (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbduxsigma_getstatusinfo(struct comedi_device *dev, int chan)
{
	struct comedi_subdevice *s = dev->read_subdev;
	struct usbduxsigma_private *devpriv = dev->private;
	u8 sysred;
	u32 val;
	int ret;

	switch (chan) {
	default:
	case 0:
		sysred = 0;		/* ADC zero */
		break;
	case 1:
		sysred = 1;		/* ADC offset */
		break;
	case 2:
		sysred = 4;		/* VCC */
		break;
	case 3:
		sysred = 8;		/* temperature */
		break;
	case 4:
		sysred = 16;		/* gain */
		break;
	case 5:
		sysred =  32;		/* ref */
		break;
	}

	devpriv->dux_commands[1] = 0x12; /* CONFIG0 */
	devpriv->dux_commands[2] = 0x80; /* CONFIG1: 2kHz sampling rate */
	devpriv->dux_commands[3] = 0x00; /* CONFIG3: diff. channels off */
	devpriv->dux_commands[4] = 0;
	devpriv->dux_commands[5] = 0;
	devpriv->dux_commands[6] = sysred;
	ret = usbbuxsigma_send_cmd(dev, USBDUXSIGMA_SINGLE_AD_CMD);
	if (ret < 0)
		return ret;

	ret = usbduxsigma_receive_cmd(dev, USBDUXSIGMA_SINGLE_AD_CMD);
	if (ret < 0)
		return ret;

	/* 32 bits big endian from the A/D converter */
	val = be32_to_cpu(get_unaligned((__be32 *)(devpriv->insn_buf + 1)));
	val &= 0x00ffffff;	/* strip status byte */

	return (int)comedi_offset_munge(s, val);
}