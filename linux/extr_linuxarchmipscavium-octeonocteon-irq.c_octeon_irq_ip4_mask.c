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
 int /*<<< orphan*/  STATUSF_IP4 ; 
 int /*<<< orphan*/  clear_c0_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spurious_interrupt () ; 

__attribute__((used)) static void octeon_irq_ip4_mask(void)
{
	clear_c0_status(STATUSF_IP4);
	spurious_interrupt();
}