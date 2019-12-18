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
struct TYPE_2__ {int yoffset; } ;
struct fb_info {TYPE_1__ var; } ;
struct fb_cursor {int enable; } ;

/* Variables and functions */
#define  CM_DRAW 130 
#define  CM_ERASE 129 
#define  CM_MOVE 128 
 scalar_t__ CTLA_REG ; 
 scalar_t__ CURS_POS_REG ; 
 unsigned int CURS_TOGGLE ; 
 int fontheight (int /*<<< orphan*/ ) ; 
 int fontwidth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p ; 
 int x ; 
 int y ; 

int g364fb_cursor(struct fb_info *info, struct fb_cursor *cursor)
{
	
	switch (cursor->enable) {
	case CM_ERASE:
		*(unsigned int *) CTLA_REG |= CURS_TOGGLE;
		break;

	case CM_MOVE:
	case CM_DRAW:
		*(unsigned int *) CTLA_REG &= ~CURS_TOGGLE;
		*(unsigned int *) CURS_POS_REG =
		    ((x * fontwidth(p)) << 12) | ((y * fontheight(p)) -
						  info->var.yoffset);
		break;
	}
	return 0;
}