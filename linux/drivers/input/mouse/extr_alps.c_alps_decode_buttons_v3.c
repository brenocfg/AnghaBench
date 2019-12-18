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
struct alps_fields {int left; int right; int middle; int ts_left; int ts_right; int ts_middle; } ;

/* Variables and functions */

__attribute__((used)) static void alps_decode_buttons_v3(struct alps_fields *f, unsigned char *p)
{
	f->left = !!(p[3] & 0x01);
	f->right = !!(p[3] & 0x02);
	f->middle = !!(p[3] & 0x04);

	f->ts_left = !!(p[3] & 0x10);
	f->ts_right = !!(p[3] & 0x20);
	f->ts_middle = !!(p[3] & 0x40);
}