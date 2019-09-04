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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ CKSEG1ADDR (int /*<<< orphan*/ ) ; 
 scalar_t__ KN02CA_MER_INTR ; 
 int /*<<< orphan*/  KN02XA_MEM_INTR ; 
 int /*<<< orphan*/  KN02XA_MER ; 
 int /*<<< orphan*/  iob () ; 

__attribute__((used)) static inline void dec_kn02xa_be_ack(void)
{
	volatile u32 *mer = (void *)CKSEG1ADDR(KN02XA_MER);
	volatile u32 *mem_intr = (void *)CKSEG1ADDR(KN02XA_MEM_INTR);

	*mer = KN02CA_MER_INTR;		/* Clear errors; keep the ARC IRQ. */
	*mem_intr = 0;			/* Any write clears the bus IRQ. */
	iob();
}