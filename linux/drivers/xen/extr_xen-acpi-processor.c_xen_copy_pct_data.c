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
struct xen_pct_register {int /*<<< orphan*/  address; int /*<<< orphan*/  reserved; int /*<<< orphan*/  bit_offset; int /*<<< orphan*/  bit_width; int /*<<< orphan*/  space_id; int /*<<< orphan*/  length; int /*<<< orphan*/  descriptor; } ;
struct acpi_pct_register {int /*<<< orphan*/  address; int /*<<< orphan*/  reserved; int /*<<< orphan*/  bit_offset; int /*<<< orphan*/  bit_width; int /*<<< orphan*/  space_id; int /*<<< orphan*/  length; int /*<<< orphan*/  descriptor; } ;

/* Variables and functions */

__attribute__((used)) static int xen_copy_pct_data(struct acpi_pct_register *pct,
			     struct xen_pct_register *dst_pct)
{
	/* It would be nice if you could just do 'memcpy(pct, dst_pct') but
	 * sadly the Xen structure did not have the proper padding so the
	 * descriptor field takes two (dst_pct) bytes instead of one (pct).
	 */
	dst_pct->descriptor = pct->descriptor;
	dst_pct->length = pct->length;
	dst_pct->space_id = pct->space_id;
	dst_pct->bit_width = pct->bit_width;
	dst_pct->bit_offset = pct->bit_offset;
	dst_pct->reserved = pct->reserved;
	dst_pct->address = pct->address;
	return 0;
}