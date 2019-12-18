#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bits_per_pixel; } ;
struct TYPE_4__ {TYPE_1__ var; } ;
struct stifb_info {scalar_t__ id; TYPE_2__ info; } ;

/* Variables and functions */
 scalar_t__ CRT_ID_VISUALIZE_EG ; 
 int /*<<< orphan*/  REG_1 ; 
 int /*<<< orphan*/  REG_2 ; 
 int /*<<< orphan*/  REG_26 ; 
 scalar_t__ S9000_ID_ARTIST ; 
 int /*<<< orphan*/  SETUP_FB (struct stifb_info*) ; 
 int /*<<< orphan*/  WRITE_WORD (int,struct stifb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
FINISH_IMAGE_COLORMAP_ACCESS(struct stifb_info *fb) 
{		
	WRITE_WORD(0x400, fb, REG_2);
	if (fb->info.var.bits_per_pixel == 32) {
		WRITE_WORD(0x83000100, fb, REG_1);
	} else {
		if (fb->id == S9000_ID_ARTIST || fb->id == CRT_ID_VISUALIZE_EG)
			WRITE_WORD(0x80000100, fb, REG_26);
		else							
			WRITE_WORD(0x80000100, fb, REG_1);
	}
	SETUP_FB(fb);
}