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
struct TYPE_2__ {int /*<<< orphan*/  exit; int /*<<< orphan*/  fixups; } ;

/* Variables and functions */
 int /*<<< orphan*/  CUBOOT_INIT () ; 
 int /*<<< orphan*/  _dtb_start ; 
 int /*<<< orphan*/  fdt_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hotfoot_fixups ; 
 int /*<<< orphan*/  ibm40x_dbcr_reset ; 
 TYPE_1__ platform_ops ; 
 int /*<<< orphan*/  serial_console_init () ; 

void platform_init(unsigned long r3, unsigned long r4, unsigned long r5,
		   unsigned long r6, unsigned long r7)
{
	CUBOOT_INIT();
	platform_ops.fixups = hotfoot_fixups;
        platform_ops.exit = ibm40x_dbcr_reset;
	fdt_init(_dtb_start);
	serial_console_init();
}