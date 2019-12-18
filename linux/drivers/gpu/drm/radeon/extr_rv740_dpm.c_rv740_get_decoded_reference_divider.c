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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 

u32 rv740_get_decoded_reference_divider(u32 encoded_ref)
{
	u32 ref = 0;

	switch (encoded_ref) {
	case 0:
		ref = 1;
		break;
	case 16:
		ref = 2;
		break;
	case 17:
		ref = 3;
		break;
	case 18:
		ref = 2;
		break;
	case 19:
		ref = 3;
		break;
	case 20:
		ref = 4;
		break;
	case 21:
		ref = 5;
		break;
	default:
		DRM_ERROR("Invalid encoded Reference Divider\n");
		ref = 0;
		break;
	}

	return ref;
}