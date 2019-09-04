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
typedef  int uint32_t ;
struct graphics_object_id {int type; } ;
struct dc_bios {int dummy; } ;

/* Variables and functions */
#define  OBJECT_TYPE_CONNECTOR 129 
#define  OBJECT_TYPE_ENCODER 128 

__attribute__((used)) static uint32_t bios_parser_get_dst_number(struct dc_bios *dcb,
	struct graphics_object_id id)
{
	/* connector has 1 Dest, encoder has 0 Dest */
	switch (id.type) {
	case OBJECT_TYPE_ENCODER:
		return 0;
	case OBJECT_TYPE_CONNECTOR:
		return 1;
	default:
		return 0;
	}
}