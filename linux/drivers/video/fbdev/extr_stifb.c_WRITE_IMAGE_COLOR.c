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
struct stifb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_3 ; 
 int /*<<< orphan*/  REG_4 ; 
 int /*<<< orphan*/  SETUP_HW (struct stifb_info*) ; 
 int /*<<< orphan*/  WRITE_WORD (int,struct stifb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
WRITE_IMAGE_COLOR(struct stifb_info *fb, int index, int color) 
{
	SETUP_HW(fb);
	WRITE_WORD(((0x100+index)<<2), fb, REG_3);
	WRITE_WORD(color, fb, REG_4);
}