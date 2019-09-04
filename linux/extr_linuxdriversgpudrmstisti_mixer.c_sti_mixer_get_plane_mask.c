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
struct sti_plane {int desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAM_CTL_BACK_MASK ; 
 int /*<<< orphan*/  GAM_CTL_CURSOR_MASK ; 
 int /*<<< orphan*/  GAM_CTL_GDP0_MASK ; 
 int /*<<< orphan*/  GAM_CTL_GDP1_MASK ; 
 int /*<<< orphan*/  GAM_CTL_GDP2_MASK ; 
 int /*<<< orphan*/  GAM_CTL_GDP3_MASK ; 
 int /*<<< orphan*/  GAM_CTL_VID0_MASK ; 
#define  STI_BACK 134 
#define  STI_CURSOR 133 
#define  STI_GDP_0 132 
#define  STI_GDP_1 131 
#define  STI_GDP_2 130 
#define  STI_GDP_3 129 
#define  STI_HQVDP_0 128 

__attribute__((used)) static u32 sti_mixer_get_plane_mask(struct sti_plane *plane)
{
	switch (plane->desc) {
	case STI_BACK:
		return GAM_CTL_BACK_MASK;
	case STI_GDP_0:
		return GAM_CTL_GDP0_MASK;
	case STI_GDP_1:
		return GAM_CTL_GDP1_MASK;
	case STI_GDP_2:
		return GAM_CTL_GDP2_MASK;
	case STI_GDP_3:
		return GAM_CTL_GDP3_MASK;
	case STI_HQVDP_0:
		return GAM_CTL_VID0_MASK;
	case STI_CURSOR:
		return GAM_CTL_CURSOR_MASK;
	default:
		return 0;
	}
}