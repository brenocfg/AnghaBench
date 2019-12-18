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
struct vc_data {int dummy; } ;

/* Variables and functions */
 unsigned short* screenpos (struct vc_data*,int,int) ; 

unsigned short *screen_pos(struct vc_data *vc, int w_offset, int viewed)
{
	return screenpos(vc, 2 * w_offset, viewed);
}