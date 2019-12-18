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
struct vc_data {int /*<<< orphan*/  vc_video_erase_char; int /*<<< orphan*/  vc_cols; } ;
struct sti_struct {int dummy; } ;
typedef  enum con_scroll { ____Placeholder_con_scroll } con_scroll ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ERASE ; 
#define  SM_DOWN 129 
#define  SM_UP 128 
 int /*<<< orphan*/  sti_bmove (struct sti_struct*,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sti_clear (struct sti_struct*,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sticon_cursor (struct vc_data*,int /*<<< orphan*/ ) ; 
 struct sti_struct* sticon_sti ; 
 scalar_t__ vga_is_gfx ; 

__attribute__((used)) static bool sticon_scroll(struct vc_data *conp, unsigned int t,
		unsigned int b, enum con_scroll dir, unsigned int count)
{
    struct sti_struct *sti = sticon_sti;

    if (vga_is_gfx)
        return false;

    sticon_cursor(conp, CM_ERASE);

    switch (dir) {
    case SM_UP:
	sti_bmove(sti, t + count, 0, t, 0, b - t - count, conp->vc_cols);
	sti_clear(sti, b - count, 0, count, conp->vc_cols, conp->vc_video_erase_char);
	break;

    case SM_DOWN:
	sti_bmove(sti, t, 0, t + count, 0, b - t - count, conp->vc_cols);
	sti_clear(sti, t, 0, count, conp->vc_cols, conp->vc_video_erase_char);
	break;
    }

    return false;
}