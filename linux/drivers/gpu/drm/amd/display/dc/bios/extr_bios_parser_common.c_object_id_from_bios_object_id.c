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
typedef  int /*<<< orphan*/  uint32_t ;
struct graphics_object_id {int /*<<< orphan*/  member_0; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
typedef  enum object_enum_id { ____Placeholder_object_enum_id } object_enum_id ;

/* Variables and functions */
 int ENUM_ID_UNKNOWN ; 
 int OBJECT_TYPE_UNKNOWN ; 
 struct graphics_object_id dal_graphics_object_id_init (int /*<<< orphan*/ ,int,int) ; 
 int enum_id_from_bios_object_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  id_from_bios_object_id (int,int /*<<< orphan*/ ) ; 
 int object_type_from_bios_object_id (int /*<<< orphan*/ ) ; 

struct graphics_object_id object_id_from_bios_object_id(uint32_t bios_object_id)
{
	enum object_type type;
	enum object_enum_id enum_id;
	struct graphics_object_id go_id = { 0 };

	type = object_type_from_bios_object_id(bios_object_id);

	if (OBJECT_TYPE_UNKNOWN == type)
		return go_id;

	enum_id = enum_id_from_bios_object_id(bios_object_id);

	if (ENUM_ID_UNKNOWN == enum_id)
		return go_id;

	go_id = dal_graphics_object_id_init(
			id_from_bios_object_id(type, bios_object_id), enum_id, type);

	return go_id;
}