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
struct pvr2_ctrl {TYPE_1__* hdw; } ;
struct TYPE_2__ {scalar_t__ enc_unsafe_stale; scalar_t__ enc_stale; } ;

/* Variables and functions */

__attribute__((used)) static void ctrl_cx2341x_clear_dirty(struct pvr2_ctrl *cptr)
{
	cptr->hdw->enc_stale = 0;
	cptr->hdw->enc_unsafe_stale = 0;
}