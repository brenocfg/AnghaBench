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
struct smtcfb_info {TYPE_1__* fb; } ;
struct TYPE_2__ {int /*<<< orphan*/ * screen_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smtc_unmap_smem(struct smtcfb_info *sfb)
{
	if (sfb && sfb->fb->screen_base) {
		iounmap(sfb->fb->screen_base);
		sfb->fb->screen_base = NULL;
	}
}