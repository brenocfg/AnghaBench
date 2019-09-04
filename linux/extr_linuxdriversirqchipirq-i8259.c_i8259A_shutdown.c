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

/* Variables and functions */
 int /*<<< orphan*/  PIC_MASTER_IMR ; 
 int /*<<< orphan*/  PIC_SLAVE_IMR ; 
 scalar_t__ i8259A_auto_eoi ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i8259A_shutdown(void)
{
	/* Put the i8259A into a quiescent state that
	 * the kernel initialization code can get it
	 * out of.
	 */
	if (i8259A_auto_eoi >= 0) {
		outb(0xff, PIC_MASTER_IMR);	/* mask all of 8259A-1 */
		outb(0xff, PIC_SLAVE_IMR);	/* mask all of 8259A-2 */
	}
}