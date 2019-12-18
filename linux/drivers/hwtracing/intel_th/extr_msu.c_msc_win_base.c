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
struct msc_window {int dummy; } ;
struct msc_block_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msc_win_base_sg (struct msc_window*) ; 
 struct msc_block_desc* sg_virt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct msc_block_desc *msc_win_base(struct msc_window *win)
{
	return sg_virt(msc_win_base_sg(win));
}