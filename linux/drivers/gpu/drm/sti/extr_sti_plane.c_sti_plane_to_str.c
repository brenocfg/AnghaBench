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
struct sti_plane {int desc; } ;

/* Variables and functions */
#define  STI_CURSOR 133 
#define  STI_GDP_0 132 
#define  STI_GDP_1 131 
#define  STI_GDP_2 130 
#define  STI_GDP_3 129 
#define  STI_HQVDP_0 128 

const char *sti_plane_to_str(struct sti_plane *plane)
{
	switch (plane->desc) {
	case STI_GDP_0:
		return "GDP0";
	case STI_GDP_1:
		return "GDP1";
	case STI_GDP_2:
		return "GDP2";
	case STI_GDP_3:
		return "GDP3";
	case STI_HQVDP_0:
		return "HQVDP0";
	case STI_CURSOR:
		return "CURSOR";
	default:
		return "<UNKNOWN PLANE>";
	}
}