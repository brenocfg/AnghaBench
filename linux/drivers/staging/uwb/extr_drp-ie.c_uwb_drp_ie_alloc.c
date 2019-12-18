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
struct TYPE_2__ {int /*<<< orphan*/  element_id; } ;
struct uwb_ie_drp {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UWB_IE_DRP ; 
 int /*<<< orphan*/  UWB_NUM_ZONES ; 
 int /*<<< orphan*/  allocs ; 
 struct uwb_ie_drp* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_size (struct uwb_ie_drp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct uwb_ie_drp *uwb_drp_ie_alloc(void)
{
	struct uwb_ie_drp *drp_ie;

	drp_ie = kzalloc(struct_size(drp_ie, allocs, UWB_NUM_ZONES),
			 GFP_KERNEL);
	if (drp_ie)
		drp_ie->hdr.element_id = UWB_IE_DRP;
	return drp_ie;
}