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
struct host1x_channel_list {int /*<<< orphan*/  channels; int /*<<< orphan*/  allocated_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void host1x_channel_list_free(struct host1x_channel_list *chlist)
{
	kfree(chlist->allocated_channels);
	kfree(chlist->channels);
}