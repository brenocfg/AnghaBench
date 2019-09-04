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
 unsigned long ALIGN (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONFIG_PHYSICAL_ALIGN ; 
 int /*<<< orphan*/  debug_putstr (char*) ; 
 scalar_t__ memmap_too_large ; 
 int /*<<< orphan*/  process_e820_entries (unsigned long,unsigned long) ; 
 scalar_t__ process_efi_entries (unsigned long,unsigned long) ; 
 unsigned long slots_fetch_random () ; 

__attribute__((used)) static unsigned long find_random_phys_addr(unsigned long minimum,
					   unsigned long image_size)
{
	/* Check if we had too many memmaps. */
	if (memmap_too_large) {
		debug_putstr("Aborted memory entries scan (more than 4 memmap= args)!\n");
		return 0;
	}

	/* Make sure minimum is aligned. */
	minimum = ALIGN(minimum, CONFIG_PHYSICAL_ALIGN);

	if (process_efi_entries(minimum, image_size))
		return slots_fetch_random();

	process_e820_entries(minimum, image_size);
	return slots_fetch_random();
}