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
struct tb_nhi {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ REG_RING_INTERRUPT_BASE ; 
 scalar_t__ REG_RING_NOTIFY_BASE ; 
 int RING_INTERRUPT_REG_COUNT (struct tb_nhi*) ; 
 int RING_NOTIFY_REG_COUNT (struct tb_nhi*) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void nhi_disable_interrupts(struct tb_nhi *nhi)
{
	int i = 0;
	/* disable interrupts */
	for (i = 0; i < RING_INTERRUPT_REG_COUNT(nhi); i++)
		iowrite32(0, nhi->iobase + REG_RING_INTERRUPT_BASE + 4 * i);

	/* clear interrupt status bits */
	for (i = 0; i < RING_NOTIFY_REG_COUNT(nhi); i++)
		ioread32(nhi->iobase + REG_RING_NOTIFY_BASE + 4 * i);
}