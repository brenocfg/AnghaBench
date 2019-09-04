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
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct vpd_section {int /*<<< orphan*/  baseaddr; TYPE_1__ bin_attr; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int VPD_OK ; 
 int vpd_decode_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,struct vpd_section*) ; 
 int /*<<< orphan*/  vpd_section_attrib_add ; 

__attribute__((used)) static int vpd_section_create_attribs(struct vpd_section *sec)
{
	s32 consumed;
	int ret;

	consumed = 0;
	do {
		ret = vpd_decode_string(sec->bin_attr.size, sec->baseaddr,
					&consumed, vpd_section_attrib_add, sec);
	} while (ret == VPD_OK);

	return 0;
}