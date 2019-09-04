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
struct graphics_object_id {int type; int /*<<< orphan*/  enum_id; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENUM_ID_UNKNOWN ; 
#define  OBJECT_TYPE_ENGINE 130 
#define  OBJECT_TYPE_GPU 129 
#define  OBJECT_TYPE_UNKNOWN 128 

__attribute__((used)) static bool dal_graphics_object_id_is_valid(struct graphics_object_id id)
{
	bool rc = true;

	switch (id.type) {
	case OBJECT_TYPE_UNKNOWN:
		rc = false;
		break;
	case OBJECT_TYPE_GPU:
	case OBJECT_TYPE_ENGINE:
		/* do NOT check for id.id == 0 */
		if (id.enum_id == ENUM_ID_UNKNOWN)
			rc = false;
		break;
	default:
		if (id.id == 0 || id.enum_id == ENUM_ID_UNKNOWN)
			rc = false;
		break;
	}

	return rc;
}