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
struct scpi_drvinfo {int num_chans; TYPE_1__* channels; } ;
struct TYPE_2__ {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scpi_free_channels(void *data)
{
	struct scpi_drvinfo *info = data;
	int i;

	for (i = 0; i < info->num_chans; i++)
		mbox_free_channel(info->channels[i].chan);
}