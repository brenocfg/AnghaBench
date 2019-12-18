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
 int /*<<< orphan*/  VDE_INTERRUPT ; 
 scalar_t__ viafb_enabled_ints ; 
 int /*<<< orphan*/  viafb_mmio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void viafb_int_init(void)
{
	viafb_enabled_ints = 0;

	viafb_mmio_write(VDE_INTERRUPT, 0);
}