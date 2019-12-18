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
struct vc_data {int vc_complement_mask; int /*<<< orphan*/  vc_rows; int /*<<< orphan*/  vc_cols; struct vc_data** vc_display_fg; } ;

/* Variables and functions */
 struct vc_data* mda_display_fg ; 
 int /*<<< orphan*/  mda_num_columns ; 
 int /*<<< orphan*/  mda_num_lines ; 
 int /*<<< orphan*/  vc_resize (struct vc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mdacon_init(struct vc_data *c, int init)
{
	c->vc_complement_mask = 0x0800;	 /* reverse video */
	c->vc_display_fg = &mda_display_fg;

	if (init) {
		c->vc_cols = mda_num_columns;
		c->vc_rows = mda_num_lines;
	} else
		vc_resize(c, mda_num_columns, mda_num_lines);

	/* make the first MDA console visible */

	if (mda_display_fg == NULL)
		mda_display_fg = c;
}