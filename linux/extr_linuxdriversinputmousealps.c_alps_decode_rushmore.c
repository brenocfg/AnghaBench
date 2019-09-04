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
struct psmouse {int dummy; } ;
struct TYPE_2__ {unsigned char x; unsigned char y; } ;
struct alps_fields {int first_mp; int is_mp; unsigned char x_map; unsigned char y_map; unsigned char pressure; TYPE_1__ st; scalar_t__ fingers; } ;

/* Variables and functions */
 int /*<<< orphan*/  alps_decode_buttons_v3 (struct alps_fields*,unsigned char*) ; 
 scalar_t__ max (unsigned char,unsigned char) ; 

__attribute__((used)) static int alps_decode_rushmore(struct alps_fields *f, unsigned char *p,
				 struct psmouse *psmouse)
{
	f->first_mp = !!(p[4] & 0x40);
	f->is_mp = !!(p[5] & 0x40);

	if (f->is_mp) {
		f->fingers = max((p[5] & 0x3), ((p[5] >> 2) & 0x3)) + 1;
		f->x_map = ((p[5] & 0x10) << 11) |
			   ((p[4] & 0x7e) << 8) |
			   ((p[1] & 0x7f) << 2) |
			   ((p[0] & 0x30) >> 4);
		f->y_map = ((p[5] & 0x20) << 6) |
			   ((p[3] & 0x70) << 4) |
			   ((p[2] & 0x7f) << 1) |
			   (p[4] & 0x01);
	} else {
		f->st.x = ((p[1] & 0x7f) << 4) | ((p[4] & 0x30) >> 2) |
		       ((p[0] & 0x30) >> 4);
		f->st.y = ((p[2] & 0x7f) << 4) | (p[4] & 0x0f);
		f->pressure = p[5] & 0x7f;

		alps_decode_buttons_v3(f, p);
	}

	return 0;
}