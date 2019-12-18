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
struct device {int dummy; } ;

/* Variables and functions */
#define  WM8400_INTERRUPT_LEVELS 130 
#define  WM8400_INTERRUPT_STATUS_1 129 
#define  WM8400_SHUTDOWN_REASON 128 

__attribute__((used)) static bool wm8400_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case WM8400_INTERRUPT_STATUS_1:
	case WM8400_INTERRUPT_LEVELS:
	case WM8400_SHUTDOWN_REASON:
		return true;
	default:
		return false;
	}
}