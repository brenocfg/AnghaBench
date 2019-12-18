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
struct vc_data {int /*<<< orphan*/  vc_video_erase_char; } ;

/* Variables and functions */
 int /*<<< orphan*/ * mda_addr (int,int) ; 
 int /*<<< orphan*/  mda_convert_attr (int /*<<< orphan*/ ) ; 
 int mda_num_columns ; 
 int /*<<< orphan*/  scr_memsetw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mdacon_clear(struct vc_data *c, int y, int x, 
			  int height, int width)
{
	u16 *dest = mda_addr(x, y);
	u16 eattr = mda_convert_attr(c->vc_video_erase_char);

	if (width <= 0 || height <= 0)
		return;

	if (x==0 && width==mda_num_columns) {
		scr_memsetw(dest, eattr, height*width*2);
	} else {
		for (; height > 0; height--, dest+=mda_num_columns)
			scr_memsetw(dest, eattr, width*2);
	}
}