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
typedef  int /*<<< orphan*/  amb_dev ;

/* Variables and functions */
 int AMB_INTERRUPT_BITS ; 
 int /*<<< orphan*/  amb_mem ; 
 int /*<<< orphan*/  interrupt_control ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rd_plain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr_plain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void interrupts_off (amb_dev * dev) {
  wr_plain (dev, offsetof(amb_mem, interrupt_control),
	    rd_plain (dev, offsetof(amb_mem, interrupt_control))
	    &~ AMB_INTERRUPT_BITS);
}