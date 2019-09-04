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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  UV_BIOS_SET_LEGACY_VGA_TARGET ; 
 int uv_bios_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int uv_bios_set_legacy_vga_target(bool decode, int domain, int bus)
{
	return uv_bios_call(UV_BIOS_SET_LEGACY_VGA_TARGET,
				(u64)decode, (u64)domain, (u64)bus, 0, 0);
}