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
typedef  int /*<<< orphan*/  u16 ;
struct vc_data {int vc_hi_font_mask; scalar_t__ vc_origin; } ;

/* Variables and functions */
 int scr_readw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * screen_pos (struct vc_data*,int,int) ; 

__attribute__((used)) static unsigned char get_attributes(struct vc_data *vc, u16 *pos)
{
	pos = screen_pos(vc, pos - (u16 *)vc->vc_origin, 1);
	return (scr_readw(pos) & ~vc->vc_hi_font_mask) >> 8;
}