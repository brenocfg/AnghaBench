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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int /*<<< orphan*/  VBE_DISPI_INDEX_ID ; 
 int /*<<< orphan*/  VBE_DISPI_IOPORT_DATA ; 
 scalar_t__ inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbox_write_ioport (int /*<<< orphan*/ ,scalar_t__) ; 

bool vbox_check_supported(u16 id)
{
	u16 dispi_id;

	vbox_write_ioport(VBE_DISPI_INDEX_ID, id);
	dispi_id = inw(VBE_DISPI_IOPORT_DATA);

	return dispi_id == id;
}