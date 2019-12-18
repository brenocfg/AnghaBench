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
typedef  int /*<<< orphan*/  u32 ;
struct komeda_data_flow_cfg {int /*<<< orphan*/  total_in_w; int /*<<< orphan*/  total_in_h; int /*<<< orphan*/  in_w; int /*<<< orphan*/  in_h; } ;

/* Variables and functions */
 scalar_t__ drm_rotation_90_or_270 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
komeda_rotate_data_flow(struct komeda_data_flow_cfg *dflow, u32 rot)
{
	if (drm_rotation_90_or_270(rot)) {
		swap(dflow->in_h, dflow->in_w);
		swap(dflow->total_in_h, dflow->total_in_w);
	}
}