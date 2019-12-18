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
struct slic_device {int dummy; } ;

/* Variables and functions */
 int SLIC_ISR_CMD ; 
 int SLIC_ISR_ERR ; 
 int SLIC_ISR_LEVENT ; 
 int SLIC_ISR_RCV ; 
 int SLIC_ISR_UPC_MASK ; 
 int /*<<< orphan*/  slic_handle_err_irq (struct slic_device*,int) ; 
 int /*<<< orphan*/  slic_handle_link_change (struct slic_device*) ; 
 int /*<<< orphan*/  slic_handle_receive (struct slic_device*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  slic_handle_upr_irq (struct slic_device*,int) ; 
 int /*<<< orphan*/  slic_xmit_complete (struct slic_device*) ; 

__attribute__((used)) static void slic_handle_irq(struct slic_device *sdev, u32 isr,
			    unsigned int todo, unsigned int *done)
{
	if (isr & SLIC_ISR_ERR)
		slic_handle_err_irq(sdev, isr);

	if (isr & SLIC_ISR_LEVENT)
		slic_handle_link_change(sdev);

	if (isr & SLIC_ISR_UPC_MASK)
		slic_handle_upr_irq(sdev, isr);

	if (isr & SLIC_ISR_RCV)
		slic_handle_receive(sdev, todo, done);

	if (isr & SLIC_ISR_CMD)
		slic_xmit_complete(sdev);
}