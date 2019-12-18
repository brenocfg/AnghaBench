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
struct saa7146_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,int) ; 
 int tuner_write (struct saa7146_dev*,int,int*) ; 

__attribute__((used)) static int ves1820_set_tv_freq(struct saa7146_dev *dev, u32 freq)
{
	u32 div;
	u8 config;
	u8 buf[4];

	dprintk(4, "freq: 0x%08x\n", freq);

	/* magic number: 614. tuning with the frequency given by v4l2
	   is always off by 614*62.5 = 38375 kHz...*/
	div = freq + 614;

	buf[0] = (div >> 8) & 0x7f;
	buf[1] = div & 0xff;
	buf[2] = 0x8e;

	if (freq < (u32) (16 * 168.25))
		config = 0xa0;
	else if (freq < (u32) (16 * 447.25))
		config = 0x90;
	else
		config = 0x30;
	config &= ~0x02;

	buf[3] = config;

	return tuner_write(dev, 0x61, buf);
}