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
struct mmp_path {int dummy; } ;
struct TYPE_2__ {void* reg_base; } ;

/* Variables and functions */
 TYPE_1__* path_to_ctrl (struct mmp_path*) ; 

__attribute__((used)) static inline void *ctrl_regs(struct mmp_path *path)
{
	return path_to_ctrl(path)->reg_base;
}