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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int dummy; } ;
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 unsigned int S626_MC1_A2OUT ; 
 scalar_t__ S626_P_FB_BUFFER2 ; 
 scalar_t__ S626_P_MC1 ; 
 scalar_t__ S626_P_SSR ; 
 unsigned int S626_SSR_AF2_OUT ; 
 unsigned int readl (scalar_t__) ; 
#define  s626_send_dac_wait_fb_buffer2_msb_00 131 
#define  s626_send_dac_wait_fb_buffer2_msb_ff 130 
#define  s626_send_dac_wait_not_mc1_a2out 129 
#define  s626_send_dac_wait_ssr_af2_out 128 

__attribute__((used)) static int s626_send_dac_eoc(struct comedi_device *dev,
			     struct comedi_subdevice *s,
			     struct comedi_insn *insn,
			     unsigned long context)
{
	unsigned int status;

	switch (context) {
	case s626_send_dac_wait_not_mc1_a2out:
		status = readl(dev->mmio + S626_P_MC1);
		if (!(status & S626_MC1_A2OUT))
			return 0;
		break;
	case s626_send_dac_wait_ssr_af2_out:
		status = readl(dev->mmio + S626_P_SSR);
		if (status & S626_SSR_AF2_OUT)
			return 0;
		break;
	case s626_send_dac_wait_fb_buffer2_msb_00:
		status = readl(dev->mmio + S626_P_FB_BUFFER2);
		if (!(status & 0xff000000))
			return 0;
		break;
	case s626_send_dac_wait_fb_buffer2_msb_ff:
		status = readl(dev->mmio + S626_P_FB_BUFFER2);
		if (status & 0xff000000)
			return 0;
		break;
	default:
		return -EINVAL;
	}
	return -EBUSY;
}