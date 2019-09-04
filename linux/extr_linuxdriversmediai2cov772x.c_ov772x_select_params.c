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
struct v4l2_mbus_framefmt {scalar_t__ code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct ov772x_win_size {int dummy; } ;
struct ov772x_color_format {scalar_t__ code; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct ov772x_color_format*) ; 
 struct ov772x_color_format* ov772x_cfmts ; 
 struct ov772x_win_size* ov772x_select_win (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ov772x_select_params(const struct v4l2_mbus_framefmt *mf,
				 const struct ov772x_color_format **cfmt,
				 const struct ov772x_win_size **win)
{
	unsigned int i;

	/* Select a format. */
	*cfmt = &ov772x_cfmts[0];

	for (i = 0; i < ARRAY_SIZE(ov772x_cfmts); i++) {
		if (mf->code == ov772x_cfmts[i].code) {
			*cfmt = &ov772x_cfmts[i];
			break;
		}
	}

	/* Select a window size. */
	*win = ov772x_select_win(mf->width, mf->height);
}