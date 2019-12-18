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
struct net_device {int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DLM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ser12_set_divisor(struct net_device *dev,
                                     unsigned int divisor)
{
        outb(0x81, LCR(dev->base_addr));        /* DLAB = 1 */
        outb(divisor, DLL(dev->base_addr));
        outb(divisor >> 8, DLM(dev->base_addr));
        outb(0x01, LCR(dev->base_addr));        /* word length = 6 */
        /*
         * make sure the next interrupt is generated;
         * 0 must be used to power the modem; the modem draws its
         * power from the TxD line
         */
        outb(0x00, THR(dev->base_addr));
        /*
         * it is important not to set the divider while transmitting;
         * this reportedly makes some UARTs generating interrupts
         * in the hundredthousands per second region
         * Reported by: Ignacio.Arenaza@studi.epfl.ch (Ignacio Arenaza Nuno)
         */
}