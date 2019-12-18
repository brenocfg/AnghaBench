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
struct bttv {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  BT848_ADC ; 
 int BT848_ADC_AGC_EN ; 
 int BT848_ADC_RESERVED ; 
 int /*<<< orphan*/  BT848_GPIO_DMA_CTL ; 
 int BT848_GPIO_DMA_CTL_GPCLKMODE ; 
 int btread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bttv_I2CRead (struct bttv*,int,int /*<<< orphan*/ *) ; 
 int bttv_I2CWrite (struct bttv*,int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ bttv_gpio ; 
 int /*<<< orphan*/  bttv_gpio_tracking (struct bttv*,char*) ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_bits (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_inout (int,int) ; 
 int /*<<< orphan*/  gpio_write (int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void init_PXC200(struct bttv *btv)
{
	static int vals[] = { 0x08, 0x09, 0x0a, 0x0b, 0x0d, 0x0d, 0x01, 0x02,
			      0x03, 0x04, 0x05, 0x06, 0x00 };
	unsigned int i;
	int tmp;
	u32 val;

	/* Initialise GPIO-connevted stuff */
	gpio_inout(0xffffff, (1<<13));
	gpio_write(0);
	udelay(3);
	gpio_write(1<<13);
	/* GPIO inputs are pulled up, so no need to drive
	 * reset pin any longer */
	gpio_bits(0xffffff, 0);
	if (bttv_gpio)
		bttv_gpio_tracking(btv,"pxc200");

	/*  we could/should try and reset/control the AD pots? but
	    right now  we simply  turned off the crushing.  Without
	    this the AGC drifts drifts
	    remember the EN is reverse logic -->
	    setting BT848_ADC_AGC_EN disable the AGC
	    tboult@eecs.lehigh.edu
	*/

	btwrite(BT848_ADC_RESERVED|BT848_ADC_AGC_EN, BT848_ADC);

	/*	Initialise MAX517 DAC */
	pr_info("Setting DAC reference voltage level ...\n");
	bttv_I2CWrite(btv,0x5E,0,0x80,1);

	/*	Initialise 12C508 PIC */
	/*	The I2CWrite and I2CRead commands are actually to the
	 *	same chips - but the R/W bit is included in the address
	 *	argument so the numbers are different */


	pr_info("Initialising 12C508 PIC chip ...\n");

	/* First of all, enable the clock line. This is used in the PXC200-F */
	val = btread(BT848_GPIO_DMA_CTL);
	val |= BT848_GPIO_DMA_CTL_GPCLKMODE;
	btwrite(val, BT848_GPIO_DMA_CTL);

	/* Then, push to 0 the reset pin long enough to reset the *
	 * device same as above for the reset line, but not the same
	 * value sent to the GPIO-connected stuff
	 * which one is the good one? */
	gpio_inout(0xffffff,(1<<2));
	gpio_write(0);
	udelay(10);
	gpio_write(1<<2);

	for (i = 0; i < ARRAY_SIZE(vals); i++) {
		tmp=bttv_I2CWrite(btv,0x1E,0,vals[i],1);
		if (tmp != -1) {
			pr_info("I2C Write(%2.2x) = %i\nI2C Read () = %2.2x\n\n",
			       vals[i],tmp,bttv_I2CRead(btv,0x1F,NULL));
		}
	}

	pr_info("PXC200 Initialised\n");
}