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
struct saa7134_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_FIFO_SIZE ; 
 int /*<<< orphan*/  SAA7134_MAIN_CTRL ; 
 int SAA7134_MAIN_CTRL_APLLE ; 
 int SAA7134_MAIN_CTRL_EBDAC ; 
 int SAA7134_MAIN_CTRL_ESFE ; 
 int SAA7134_MAIN_CTRL_EVFE1 ; 
 int SAA7134_MAIN_CTRL_EVFE2 ; 
 int SAA7134_MAIN_CTRL_EXOSC ; 
 int SAA7134_MAIN_CTRL_VPLLE ; 
 int /*<<< orphan*/  SAA7134_SOURCE_TIMING2 ; 
 int /*<<< orphan*/  SAA7134_SPECIAL_MODE ; 
 int /*<<< orphan*/  SAA7134_THRESHOULD ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saa_writel (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int saa7134_hw_enable1(struct saa7134_dev *dev)
{
	/* RAM FIFO config */
	saa_writel(SAA7134_FIFO_SIZE, 0x08070503);
	saa_writel(SAA7134_THRESHOULD, 0x02020202);

	/* enable audio + video processing */
	saa_writel(SAA7134_MAIN_CTRL,
			SAA7134_MAIN_CTRL_VPLLE |
			SAA7134_MAIN_CTRL_APLLE |
			SAA7134_MAIN_CTRL_EXOSC |
			SAA7134_MAIN_CTRL_EVFE1 |
			SAA7134_MAIN_CTRL_EVFE2 |
			SAA7134_MAIN_CTRL_ESFE  |
			SAA7134_MAIN_CTRL_EBDAC);

	/*
	* Initialize OSS _after_ enabling audio clock PLL and audio processing.
	* OSS initialization writes to registers via the audio DSP; these
	* writes will fail unless the audio clock has been started.  At worst,
	* audio will not work.
	*/

	/* enable peripheral devices */
	saa_writeb(SAA7134_SPECIAL_MODE, 0x01);

	/* set vertical line numbering start (vbi needs this) */
	saa_writeb(SAA7134_SOURCE_TIMING2, 0x20);

	return 0;
}