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
struct vc_data {int vc_size_row; scalar_t__ vc_origin; } ;
struct fbcon_display {int dummy; } ;

/* Variables and functions */
 unsigned short* advance_row (unsigned short*,int) ; 
 int /*<<< orphan*/  console_conditional_schedule () ; 
 int /*<<< orphan*/  fbcon_putcs (struct vc_data*,unsigned short*,int,int,int) ; 
 unsigned short scr_readw (unsigned short*) ; 
 int /*<<< orphan*/  scr_writew (unsigned short,unsigned short*) ; 

__attribute__((used)) static void fbcon_redraw(struct vc_data *vc, struct fbcon_display *p,
			 int line, int count, int offset)
{
	unsigned short *d = (unsigned short *)
	    (vc->vc_origin + vc->vc_size_row * line);
	unsigned short *s = d + offset;

	while (count--) {
		unsigned short *start = s;
		unsigned short *le = advance_row(s, 1);
		unsigned short c;
		int x = 0;
		unsigned short attr = 1;

		do {
			c = scr_readw(s);
			if (attr != (c & 0xff00)) {
				attr = c & 0xff00;
				if (s > start) {
					fbcon_putcs(vc, start, s - start,
						    line, x);
					x += s - start;
					start = s;
				}
			}
			if (c == scr_readw(d)) {
				if (s > start) {
					fbcon_putcs(vc, start, s - start,
						     line, x);
					x += s - start + 1;
					start = s + 1;
				} else {
					x++;
					start++;
				}
			}
			scr_writew(c, d);
			console_conditional_schedule();
			s++;
			d++;
		} while (s < le);
		if (s > start)
			fbcon_putcs(vc, start, s - start, line, x);
		console_conditional_schedule();
		if (offset > 0)
			line++;
		else {
			line--;
			/* NOTE: We subtract two lines from these pointers */
			s -= vc->vc_size_row;
			d -= vc->vc_size_row;
		}
	}
}