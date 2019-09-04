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
typedef  int /*<<< orphan*/  u32 ;
struct fbd {int /*<<< orphan*/  dma_ctrl; } ;

/* Variables and functions */

__attribute__((used)) static void set_dma_ctrl(struct fbd *fb_desc, u32 ctrl)
{
	fb_desc->dma_ctrl = ctrl;
}