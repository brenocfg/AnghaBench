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
struct acpi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  io_length; int /*<<< orphan*/  io_base; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ fujitsu ; 
 int /*<<< orphan*/  fujitsu_interrupt ; 
 int /*<<< orphan*/  input_fujitsu_remove () ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_fujitsu_remove(struct acpi_device *adev)
{
	free_irq(fujitsu.irq, fujitsu_interrupt);
	release_region(fujitsu.io_base, fujitsu.io_length);
	input_fujitsu_remove();
	return 0;
}