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
 int /*<<< orphan*/  object_is_on_stack (void const*) ; 
 scalar_t__ virt_addr_valid (void const*) ; 

__attribute__((used)) static bool meson_nfc_is_buffer_dma_safe(const void *buffer)
{
	if (virt_addr_valid(buffer) && (!object_is_on_stack(buffer)))
		return true;
	return false;
}