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
struct acpi_ec {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_FLAGS_STARTED ; 
 int /*<<< orphan*/  EC_FLAGS_STOPPED ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool acpi_ec_started(struct acpi_ec *ec)
{
	return test_bit(EC_FLAGS_STARTED, &ec->flags) &&
	       !test_bit(EC_FLAGS_STOPPED, &ec->flags);
}