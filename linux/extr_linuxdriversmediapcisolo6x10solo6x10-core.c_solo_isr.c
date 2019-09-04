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
struct solo_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int SOLO_IRQ_ENCODER ; 
 int SOLO_IRQ_G723 ; 
 int SOLO_IRQ_IIC ; 
 int SOLO_IRQ_P2M (int) ; 
 int SOLO_IRQ_PCI_ERR ; 
 int /*<<< orphan*/  SOLO_IRQ_STAT ; 
 int SOLO_IRQ_VIDEO_IN ; 
 int SOLO_NR_P2M ; 
 int /*<<< orphan*/  solo_enc_v4l2_isr (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_g723_isr (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_i2c_isr (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_p2m_error_isr (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_p2m_isr (struct solo_dev*,int) ; 
 int solo_reg_read (struct solo_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  solo_timer_sync (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_video_in_isr (struct solo_dev*) ; 

__attribute__((used)) static irqreturn_t solo_isr(int irq, void *data)
{
	struct solo_dev *solo_dev = data;
	u32 status;
	int i;

	status = solo_reg_read(solo_dev, SOLO_IRQ_STAT);
	if (!status)
		return IRQ_NONE;

	/* Acknowledge all interrupts immediately */
	solo_reg_write(solo_dev, SOLO_IRQ_STAT, status);

	if (status & SOLO_IRQ_PCI_ERR)
		solo_p2m_error_isr(solo_dev);

	for (i = 0; i < SOLO_NR_P2M; i++)
		if (status & SOLO_IRQ_P2M(i))
			solo_p2m_isr(solo_dev, i);

	if (status & SOLO_IRQ_IIC)
		solo_i2c_isr(solo_dev);

	if (status & SOLO_IRQ_VIDEO_IN) {
		solo_video_in_isr(solo_dev);
		solo_timer_sync(solo_dev);
	}

	if (status & SOLO_IRQ_ENCODER)
		solo_enc_v4l2_isr(solo_dev);

	if (status & SOLO_IRQ_G723)
		solo_g723_isr(solo_dev);

	return IRQ_HANDLED;
}