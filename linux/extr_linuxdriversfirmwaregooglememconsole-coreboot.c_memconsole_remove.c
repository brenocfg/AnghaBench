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
struct coreboot_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ cbmem_console ; 
 int /*<<< orphan*/  memconsole_exit () ; 
 int /*<<< orphan*/  memunmap (scalar_t__) ; 

__attribute__((used)) static int memconsole_remove(struct coreboot_device *dev)
{
	memconsole_exit();

	if (cbmem_console)
		memunmap(cbmem_console);

	return 0;
}