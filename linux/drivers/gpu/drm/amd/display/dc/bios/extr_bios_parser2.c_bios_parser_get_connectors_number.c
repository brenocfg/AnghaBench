#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint8_t ;
struct dc_bios {int dummy; } ;
struct TYPE_6__ {TYPE_2__* v1_4; } ;
struct bios_parser {TYPE_3__ object_info_tbl; } ;
struct TYPE_5__ {unsigned int number_of_path; TYPE_1__* display_path; } ;
struct TYPE_4__ {scalar_t__ encoderobjid; } ;

/* Variables and functions */
 struct bios_parser* BP_FROM_DCB (struct dc_bios*) ; 

__attribute__((used)) static uint8_t bios_parser_get_connectors_number(struct dc_bios *dcb)
{
	struct bios_parser *bp = BP_FROM_DCB(dcb);
	unsigned int count = 0;
	unsigned int i;

	for (i = 0; i < bp->object_info_tbl.v1_4->number_of_path; i++) {
		if (bp->object_info_tbl.v1_4->display_path[i].encoderobjid != 0)
			count++;
	}
	return count;
}