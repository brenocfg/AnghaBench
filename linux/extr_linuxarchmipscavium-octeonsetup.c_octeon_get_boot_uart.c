#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int OCTEON_BL_FLAG_CONSOLE_UART1 ; 
 TYPE_1__* octeon_boot_desc_ptr ; 

int octeon_get_boot_uart(void)
{
	return (octeon_boot_desc_ptr->flags & OCTEON_BL_FLAG_CONSOLE_UART1) ?
		1 : 0;
}