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
struct cxl_afu {int dummy; } ;
struct cxl {int dummy; } ;

/* Variables and functions */
 int H_STATE_NORMAL ; 
 int /*<<< orphan*/  afu_read_error_state (struct cxl_afu*,int*) ; 

__attribute__((used)) static bool guest_link_ok(struct cxl *cxl, struct cxl_afu *afu)
{
	int state;

	if (afu && (!afu_read_error_state(afu, &state))) {
		if (state == H_STATE_NORMAL)
			return true;
	}

	return false;
}