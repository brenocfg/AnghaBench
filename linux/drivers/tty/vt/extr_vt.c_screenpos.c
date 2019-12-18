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
struct vc_data {TYPE_1__* vc_sw; scalar_t__ vc_visible_origin; scalar_t__ vc_origin; } ;
struct TYPE_2__ {unsigned short* (* con_screen_pos ) (struct vc_data*,int) ;} ;

/* Variables and functions */
 unsigned short* stub1 (struct vc_data*,int) ; 

__attribute__((used)) static inline unsigned short *screenpos(struct vc_data *vc, int offset, int viewed)
{
	unsigned short *p;
	
	if (!viewed)
		p = (unsigned short *)(vc->vc_origin + offset);
	else if (!vc->vc_sw->con_screen_pos)
		p = (unsigned short *)(vc->vc_visible_origin + offset);
	else
		p = vc->vc_sw->con_screen_pos(vc, offset);
	return p;
}