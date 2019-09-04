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
struct TYPE_2__ {int /*<<< orphan*/ * dcr_offset; int /*<<< orphan*/  dcr_host; } ;

/* Variables and functions */
 TYPE_1__ cpm ; 
 unsigned int dcr_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcr_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static unsigned int cpm_set(unsigned int cpm_reg, unsigned int mask)
{
	unsigned int value;

	/* CPM controller supports 3 different types of sleep interface
	 * known as class 1, 2 and 3. For class 1 units, they are
	 * unconditionally put to sleep when the corresponding CPM bit is
	 * set. For class 2 and 3 units this is not case; if they can be
	 * put to to sleep, they will. Here we do not verify, we just
	 * set them and expect them to eventually go off when they can.
	 */
	value = dcr_read(cpm.dcr_host, cpm.dcr_offset[cpm_reg]);
	dcr_write(cpm.dcr_host, cpm.dcr_offset[cpm_reg], value | mask);

	/* return old state, to restore later if needed */
	return value;
}