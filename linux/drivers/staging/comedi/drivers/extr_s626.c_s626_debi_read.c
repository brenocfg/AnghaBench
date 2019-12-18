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
typedef  int u16 ;
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 int S626_DEBI_CMD_RDWORD ; 
 scalar_t__ S626_P_DEBIAD ; 
 scalar_t__ S626_P_DEBICMD ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  s626_debi_transfer (struct comedi_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static u16 s626_debi_read(struct comedi_device *dev, u16 addr)
{
	/* Set up DEBI control register value in shadow RAM */
	writel(S626_DEBI_CMD_RDWORD | addr, dev->mmio + S626_P_DEBICMD);

	/*  Execute the DEBI transfer. */
	s626_debi_transfer(dev);

	return readl(dev->mmio + S626_P_DEBIAD);
}