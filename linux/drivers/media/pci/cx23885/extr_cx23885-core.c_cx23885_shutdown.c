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
struct cx23885_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_EXT_INT_MSK ; 
 int /*<<< orphan*/  AUDIO_INT_INT_MSK ; 
 int /*<<< orphan*/  AUD_EXT_DMA_CTL ; 
 int /*<<< orphan*/  AUD_INT_DMA_CTL ; 
 int /*<<< orphan*/  DEV_CNTRL2 ; 
 int /*<<< orphan*/  IR_CNTRL_REG ; 
 int /*<<< orphan*/  UART_CTL ; 
 int /*<<< orphan*/  VID_A_DMA_CTL ; 
 int /*<<< orphan*/  VID_A_INT_MSK ; 
 int /*<<< orphan*/  VID_B_DMA_CTL ; 
 int /*<<< orphan*/  VID_B_INT_MSK ; 
 int /*<<< orphan*/  VID_C_DMA_CTL ; 
 int /*<<< orphan*/  VID_C_INT_MSK ; 
 int /*<<< orphan*/  cx23885_irq_disable_all (struct cx23885_dev*) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cx23885_shutdown(struct cx23885_dev *dev)
{
	/* disable RISC controller */
	cx_write(DEV_CNTRL2, 0);

	/* Disable all IR activity */
	cx_write(IR_CNTRL_REG, 0);

	/* Disable Video A/B activity */
	cx_write(VID_A_DMA_CTL, 0);
	cx_write(VID_B_DMA_CTL, 0);
	cx_write(VID_C_DMA_CTL, 0);

	/* Disable Audio activity */
	cx_write(AUD_INT_DMA_CTL, 0);
	cx_write(AUD_EXT_DMA_CTL, 0);

	/* Disable Serial port */
	cx_write(UART_CTL, 0);

	/* Disable Interrupts */
	cx23885_irq_disable_all(dev);
	cx_write(VID_A_INT_MSK, 0);
	cx_write(VID_B_INT_MSK, 0);
	cx_write(VID_C_INT_MSK, 0);
	cx_write(AUDIO_INT_INT_MSK, 0);
	cx_write(AUDIO_EXT_INT_MSK, 0);

}