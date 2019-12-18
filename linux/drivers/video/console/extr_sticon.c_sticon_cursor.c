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
struct vc_data {unsigned short* vc_screenbuf; size_t vc_x; size_t vc_y; size_t vc_cols; int vc_cursor_type; } ;

/* Variables and functions */
#define  CM_DRAW 135 
#define  CM_ERASE 134 
#define  CM_MOVE 133 
#define  CUR_BLOCK 132 
#define  CUR_LOWER_HALF 131 
#define  CUR_LOWER_THIRD 130 
#define  CUR_TWO_THIRDS 129 
#define  CUR_UNDERLINE 128 
 int /*<<< orphan*/  sti_putc (int /*<<< orphan*/ ,unsigned short,size_t,size_t) ; 
 int /*<<< orphan*/  sticon_sti ; 

__attribute__((used)) static void sticon_cursor(struct vc_data *conp, int mode)
{
    unsigned short car1;

    car1 = conp->vc_screenbuf[conp->vc_x + conp->vc_y * conp->vc_cols];
    switch (mode) {
    case CM_ERASE:
	sti_putc(sticon_sti, car1, conp->vc_y, conp->vc_x);
	break;
    case CM_MOVE:
    case CM_DRAW:
	switch (conp->vc_cursor_type & 0x0f) {
	case CUR_UNDERLINE:
	case CUR_LOWER_THIRD:
	case CUR_LOWER_HALF:
	case CUR_TWO_THIRDS:
	case CUR_BLOCK:
	    sti_putc(sticon_sti, (car1 & 255) + (0 << 8) + (7 << 11),
		     conp->vc_y, conp->vc_x);
	    break;
	}
	break;
    }
}