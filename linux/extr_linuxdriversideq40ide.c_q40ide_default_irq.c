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

__attribute__((used)) static int q40ide_default_irq(unsigned long base)
{
           switch (base) {
	            case 0x1f0: return 14;
		    case 0x170: return 15;
		    case 0x1e8: return 11;
		    default:
			return 0;
	   }
}