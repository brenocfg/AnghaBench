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
typedef  int /*<<< orphan*/  u32 ;
struct sa1100fb_info {TYPE_1__* inf; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_visual ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sa1100fb_set_visual(struct sa1100fb_info *fbi, u32 visual)
{
	if (fbi->inf->set_visual)
		fbi->inf->set_visual(visual);
}