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
struct omapfb_update_window {int x; int y; int width; int height; int format; } ;
struct list_head {int dummy; } ;
struct hwa742_request {int dummy; } ;
struct TYPE_2__ {unsigned int max_transmit_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_PREQ (int,int,int,int) ; 
 int OMAPFB_FORMAT_FLAG_TEARSYNC ; 
 int OMAPFB_FORMAT_MASK ; 
 TYPE_1__ hwa742 ; 

__attribute__((used)) static void create_req_list(struct omapfb_update_window *win,
			    struct list_head *req_head)
{
	struct hwa742_request *req;
	int x = win->x;
	int y = win->y;
	int width = win->width;
	int height = win->height;
	int color_mode;
	int flags;

	flags = win->format & ~OMAPFB_FORMAT_MASK;
	color_mode = win->format & OMAPFB_FORMAT_MASK;

	if (x & 1) {
		ADD_PREQ(x, y, 1, height);
		width--;
		x++;
		flags &= ~OMAPFB_FORMAT_FLAG_TEARSYNC;
	}
	if (width & ~1) {
		unsigned int xspan = width & ~1;
		unsigned int ystart = y;
		unsigned int yspan = height;

		if (xspan * height * 2 > hwa742.max_transmit_size) {
			yspan = hwa742.max_transmit_size / (xspan * 2);
			ADD_PREQ(x, ystart, xspan, yspan);
			ystart += yspan;
			yspan = height - yspan;
			flags &= ~OMAPFB_FORMAT_FLAG_TEARSYNC;
		}

		ADD_PREQ(x, ystart, xspan, yspan);
		x += xspan;
		width -= xspan;
		flags &= ~OMAPFB_FORMAT_FLAG_TEARSYNC;
	}
	if (width)
		ADD_PREQ(x, y, 1, height);
}