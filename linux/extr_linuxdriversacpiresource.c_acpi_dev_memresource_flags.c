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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct resource {int flags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 scalar_t__ ACPI_READ_WRITE_MEMORY ; 
 int IORESOURCE_DISABLED ; 
 int IORESOURCE_MEM ; 
 int IORESOURCE_MEM_WRITEABLE ; 
 int IORESOURCE_UNSET ; 
 int /*<<< orphan*/  acpi_dev_resource_len_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void acpi_dev_memresource_flags(struct resource *res, u64 len,
				       u8 write_protect)
{
	res->flags = IORESOURCE_MEM;

	if (!acpi_dev_resource_len_valid(res->start, res->end, len, false))
		res->flags |= IORESOURCE_DISABLED | IORESOURCE_UNSET;

	if (write_protect == ACPI_READ_WRITE_MEMORY)
		res->flags |= IORESOURCE_MEM_WRITEABLE;
}