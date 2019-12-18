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
struct yam_port {int baudrate; } ;
struct net_device {int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DLM (int /*<<< orphan*/ ) ; 
 int ENABLE_RTXINT ; 
 int /*<<< orphan*/  FCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCR (int /*<<< orphan*/ ) ; 
 int LCR_BIT8 ; 
 int LCR_DLAB ; 
 int /*<<< orphan*/  MCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR (int /*<<< orphan*/ ) ; 
 int PTT_OFF ; 
 int /*<<< orphan*/  RBR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 struct yam_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yam_set_uart(struct net_device *dev)
{
	struct yam_port *yp = netdev_priv(dev);
	int divisor = 115200 / yp->baudrate;

	outb(0, IER(dev->base_addr));
	outb(LCR_DLAB | LCR_BIT8, LCR(dev->base_addr));
	outb(divisor, DLL(dev->base_addr));
	outb(0, DLM(dev->base_addr));
	outb(LCR_BIT8, LCR(dev->base_addr));
	outb(PTT_OFF, MCR(dev->base_addr));
	outb(0x00, FCR(dev->base_addr));

	/* Flush pending irq */

	inb(RBR(dev->base_addr));
	inb(MSR(dev->base_addr));

	/* Enable rx irq */

	outb(ENABLE_RTXINT, IER(dev->base_addr));
}