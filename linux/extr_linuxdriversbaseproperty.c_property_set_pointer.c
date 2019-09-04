#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {void const* str; int /*<<< orphan*/  u64_data; int /*<<< orphan*/  u32_data; int /*<<< orphan*/  u16_data; int /*<<< orphan*/  u8_data; } ;
struct TYPE_3__ {void const* str; void const* u64_data; void const* u32_data; void const* u16_data; void const* u8_data; } ;
struct property_entry {int type; TYPE_2__ value; TYPE_1__ pointer; int /*<<< orphan*/  is_array; } ;

/* Variables and functions */
#define  DEV_PROP_STRING 132 
#define  DEV_PROP_U16 131 
#define  DEV_PROP_U32 130 
#define  DEV_PROP_U64 129 
#define  DEV_PROP_U8 128 

__attribute__((used)) static void property_set_pointer(struct property_entry *prop, const void *pointer)
{
	switch (prop->type) {
	case DEV_PROP_U8:
		if (prop->is_array)
			prop->pointer.u8_data = pointer;
		else
			prop->value.u8_data = *((u8 *)pointer);
		break;
	case DEV_PROP_U16:
		if (prop->is_array)
			prop->pointer.u16_data = pointer;
		else
			prop->value.u16_data = *((u16 *)pointer);
		break;
	case DEV_PROP_U32:
		if (prop->is_array)
			prop->pointer.u32_data = pointer;
		else
			prop->value.u32_data = *((u32 *)pointer);
		break;
	case DEV_PROP_U64:
		if (prop->is_array)
			prop->pointer.u64_data = pointer;
		else
			prop->value.u64_data = *((u64 *)pointer);
		break;
	case DEV_PROP_STRING:
		if (prop->is_array)
			prop->pointer.str = pointer;
		else
			prop->value.str = pointer;
		break;
	default:
		break;
	}
}