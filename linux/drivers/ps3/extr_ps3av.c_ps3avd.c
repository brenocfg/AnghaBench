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
struct work_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  done; int /*<<< orphan*/  ps3av_mode_old; int /*<<< orphan*/  ps3av_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 TYPE_1__* ps3av ; 
 int /*<<< orphan*/  ps3av_set_videomode_cont (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ps3avd(struct work_struct *work)
{
	ps3av_set_videomode_cont(ps3av->ps3av_mode, ps3av->ps3av_mode_old);
	complete(&ps3av->done);
}