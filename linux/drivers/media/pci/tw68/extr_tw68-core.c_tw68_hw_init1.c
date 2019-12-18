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
struct tw68_dev {int /*<<< orphan*/  slock; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  TW68_ACNTL ; 
 int /*<<< orphan*/  TW68_AGCGAIN ; 
 int /*<<< orphan*/  TW68_BRIGHT ; 
 int /*<<< orphan*/  TW68_CAP_CTL ; 
 int /*<<< orphan*/  TW68_CKILL ; 
 int /*<<< orphan*/  TW68_CLCNTL1 ; 
 int /*<<< orphan*/  TW68_CLMD ; 
 int /*<<< orphan*/  TW68_CLMPG ; 
 int /*<<< orphan*/  TW68_CLMPL ; 
 int /*<<< orphan*/  TW68_CNTRL1 ; 
 int /*<<< orphan*/  TW68_CNTRL2 ; 
 int /*<<< orphan*/  TW68_COMB ; 
 int /*<<< orphan*/  TW68_CONTRAST ; 
 int /*<<< orphan*/  TW68_CORING ; 
 int /*<<< orphan*/  TW68_CROP_HI ; 
 int /*<<< orphan*/  TW68_DMAC ; 
 int /*<<< orphan*/  TW68_GPDATA ; 
 int /*<<< orphan*/  TW68_GPIOC ; 
 int /*<<< orphan*/  TW68_GPOE ; 
 int /*<<< orphan*/  TW68_HACTIVE_LO ; 
 int /*<<< orphan*/  TW68_HDELAY_LO ; 
 int /*<<< orphan*/  TW68_HSCALE_LO ; 
 int /*<<< orphan*/  TW68_HSYNC ; 
 int /*<<< orphan*/  TW68_HUE ; 
 int /*<<< orphan*/  TW68_IAGC ; 
 int /*<<< orphan*/  TW68_IDCNTL ; 
 int /*<<< orphan*/  TW68_INFORM ; 
 int /*<<< orphan*/  TW68_INTMASK ; 
 int /*<<< orphan*/  TW68_INTSTAT ; 
 int /*<<< orphan*/  TW68_LDLY ; 
 int /*<<< orphan*/  TW68_LOOP ; 
 int /*<<< orphan*/  TW68_MISC1 ; 
 int /*<<< orphan*/  TW68_MISC2 ; 
 int /*<<< orphan*/  TW68_MISSCNT ; 
 int /*<<< orphan*/  TW68_MVSN ; 
 int /*<<< orphan*/  TW68_OPFORM ; 
 int /*<<< orphan*/  TW68_PCLAMP ; 
 int /*<<< orphan*/  TW68_PEAKWT ; 
 int /*<<< orphan*/  TW68_SAT_U ; 
 int /*<<< orphan*/  TW68_SAT_V ; 
 int /*<<< orphan*/  TW68_SCALE_HI ; 
 int /*<<< orphan*/  TW68_SDT ; 
 int /*<<< orphan*/  TW68_SDTR ; 
 int /*<<< orphan*/  TW68_SHARP2 ; 
 int /*<<< orphan*/  TW68_SHARPNESS ; 
 int /*<<< orphan*/  TW68_SYNCT ; 
 int /*<<< orphan*/  TW68_TESTREG ; 
 int /*<<< orphan*/  TW68_VACTIVE_LO ; 
 int /*<<< orphan*/  TW68_VBIC ; 
 int /*<<< orphan*/  TW68_VCNTL1 ; 
 int /*<<< orphan*/  TW68_VCNTL2 ; 
 int /*<<< orphan*/  TW68_VDELAY_LO ; 
 int /*<<< orphan*/  TW68_VSCALE_LO ; 
 int /*<<< orphan*/  TW68_VSHARP ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tw68_video_init1 (struct tw68_dev*) ; 
 int /*<<< orphan*/  tw_writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tw_writel (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tw68_hw_init1(struct tw68_dev *dev)
{
	/* Assure all interrupts are disabled */
	tw_writel(TW68_INTMASK, 0);		/* 020 */
	/* Clear any pending interrupts */
	tw_writel(TW68_INTSTAT, 0xffffffff);	/* 01C */
	/* Stop risc processor, set default buffer level */
	tw_writel(TW68_DMAC, 0x1600);

	tw_writeb(TW68_ACNTL, 0x80);	/* 218	soft reset */
	msleep(100);

	tw_writeb(TW68_INFORM, 0x40);	/* 208	mux0, 27mhz xtal */
	tw_writeb(TW68_OPFORM, 0x04);	/* 20C	analog line-lock */
	tw_writeb(TW68_HSYNC, 0);	/* 210	color-killer high sens */
	tw_writeb(TW68_ACNTL, 0x42);	/* 218	int vref #2, chroma adc off */

	tw_writeb(TW68_CROP_HI, 0x02);	/* 21C	Hactive m.s. bits */
	tw_writeb(TW68_VDELAY_LO, 0x12);/* 220	Mfg specified reset value */
	tw_writeb(TW68_VACTIVE_LO, 0xf0);
	tw_writeb(TW68_HDELAY_LO, 0x0f);
	tw_writeb(TW68_HACTIVE_LO, 0xd0);

	tw_writeb(TW68_CNTRL1, 0xcd);	/* 230	Wide Chroma BPF B/W
					 *	Secam reduction, Adap comb for
					 *	NTSC, Op Mode 1 */

	tw_writeb(TW68_VSCALE_LO, 0);	/* 234 */
	tw_writeb(TW68_SCALE_HI, 0x11);	/* 238 */
	tw_writeb(TW68_HSCALE_LO, 0);	/* 23c */
	tw_writeb(TW68_BRIGHT, 0);	/* 240 */
	tw_writeb(TW68_CONTRAST, 0x5c);	/* 244 */
	tw_writeb(TW68_SHARPNESS, 0x51);/* 248 */
	tw_writeb(TW68_SAT_U, 0x80);	/* 24C */
	tw_writeb(TW68_SAT_V, 0x80);	/* 250 */
	tw_writeb(TW68_HUE, 0x00);	/* 254 */

	/* TODO - Check that none of these are set by control defaults */
	tw_writeb(TW68_SHARP2, 0x53);	/* 258	Mfg specified reset val */
	tw_writeb(TW68_VSHARP, 0x80);	/* 25C	Sharpness Coring val 8 */
	tw_writeb(TW68_CORING, 0x44);	/* 260	CTI and Vert Peak coring */
	tw_writeb(TW68_CNTRL2, 0x00);	/* 268	No power saving enabled */
	tw_writeb(TW68_SDT, 0x07);	/* 270	Enable shadow reg, auto-det */
	tw_writeb(TW68_SDTR, 0x7f);	/* 274	All stds recog, don't start */
	tw_writeb(TW68_CLMPG, 0x50);	/* 280	Clamp end at 40 sys clocks */
	tw_writeb(TW68_IAGC, 0x22);	/* 284	Mfg specified reset val */
	tw_writeb(TW68_AGCGAIN, 0xf0);	/* 288	AGC gain when loop disabled */
	tw_writeb(TW68_PEAKWT, 0xd8);	/* 28C	White peak threshold */
	tw_writeb(TW68_CLMPL, 0x3c);	/* 290	Y channel clamp level */
/*	tw_writeb(TW68_SYNCT, 0x38);*/	/* 294	Sync amplitude */
	tw_writeb(TW68_SYNCT, 0x30);	/* 294	Sync amplitude */
	tw_writeb(TW68_MISSCNT, 0x44);	/* 298	Horiz sync, VCR detect sens */
	tw_writeb(TW68_PCLAMP, 0x28);	/* 29C	Clamp pos from PLL sync */
	/* Bit DETV of VCNTL1 helps sync multi cams/chip board */
	tw_writeb(TW68_VCNTL1, 0x04);	/* 2A0 */
	tw_writeb(TW68_VCNTL2, 0);	/* 2A4 */
	tw_writeb(TW68_CKILL, 0x68);	/* 2A8	Mfg specified reset val */
	tw_writeb(TW68_COMB, 0x44);	/* 2AC	Mfg specified reset val */
	tw_writeb(TW68_LDLY, 0x30);	/* 2B0	Max positive luma delay */
	tw_writeb(TW68_MISC1, 0x14);	/* 2B4	Mfg specified reset val */
	tw_writeb(TW68_LOOP, 0xa5);	/* 2B8	Mfg specified reset val */
	tw_writeb(TW68_MISC2, 0xe0);	/* 2BC	Enable colour killer */
	tw_writeb(TW68_MVSN, 0);	/* 2C0 */
	tw_writeb(TW68_CLMD, 0x05);	/* 2CC	slice level auto, clamp med. */
	tw_writeb(TW68_IDCNTL, 0);	/* 2D0	Writing zero to this register
					 *	selects NTSC ID detection,
					 *	but doesn't change the
					 *	sensitivity (which has a reset
					 *	value of 1E).  Since we are
					 *	not doing auto-detection, it
					 *	has no real effect */
	tw_writeb(TW68_CLCNTL1, 0);	/* 2D4 */
	tw_writel(TW68_VBIC, 0x03);	/* 010 */
	tw_writel(TW68_CAP_CTL, 0x03);	/* 040	Enable both even & odd flds */
	tw_writel(TW68_DMAC, 0x2000);	/* patch set had 0x2080 */
	tw_writel(TW68_TESTREG, 0);	/* 02C */

	/*
	 * Some common boards, especially inexpensive single-chip models,
	 * use the GPIO bits 0-3 to control an on-board video-output mux.
	 * For these boards, we need to set up the GPIO register into
	 * "normal" mode, set bits 0-3 as output, and then set those bits
	 * zero.
	 *
	 * Eventually, it would be nice if we could identify these boards
	 * uniquely, and only do this initialisation if the board has been
	 * identify.  For the moment, however, it shouldn't hurt anything
	 * to do these steps.
	 */
	tw_writel(TW68_GPIOC, 0);	/* Set the GPIO to "normal", no ints */
	tw_writel(TW68_GPOE, 0x0f);	/* Set bits 0-3 to "output" */
	tw_writel(TW68_GPDATA, 0);	/* Set all bits to low state */

	/* Initialize the device control structures */
	mutex_init(&dev->lock);
	spin_lock_init(&dev->slock);

	/* Initialize any subsystems */
	tw68_video_init1(dev);
	return 0;
}