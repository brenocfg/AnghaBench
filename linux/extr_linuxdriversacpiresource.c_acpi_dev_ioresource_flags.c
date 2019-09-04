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
 scalar_t__ ACPI_DECODE_16 ; 
 scalar_t__ ACPI_SPARSE_TRANSLATION ; 
 int IORESOURCE_DISABLED ; 
 int IORESOURCE_IO ; 
 int IORESOURCE_IO_16BIT_ADDR ; 
 int IORESOURCE_IO_SPARSE ; 
 int IORESOURCE_UNSET ; 
 int /*<<< orphan*/  acpi_dev_resource_len_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acpi_iospace_resource_valid (struct resource*) ; 

__attribute__((used)) static void acpi_dev_ioresource_flags(struct resource *res, u64 len,
				      u8 io_decode, u8 translation_type)
{
	res->flags = IORESOURCE_IO;

	if (!acpi_dev_resource_len_valid(res->start, res->end, len, true))
		res->flags |= IORESOURCE_DISABLED | IORESOURCE_UNSET;

	if (!acpi_iospace_resource_valid(res))
		res->flags |= IORESOURCE_DISABLED | IORESOURCE_UNSET;

	if (io_decode == ACPI_DECODE_16)
		res->flags |= IORESOURCE_IO_16BIT_ADDR;
	if (translation_type == ACPI_SPARSE_TRANSLATION)
		res->flags |= IORESOURCE_IO_SPARSE;
}