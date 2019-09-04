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
struct pcmcia_device {TYPE_1__* priv; } ;
struct TYPE_2__ {int stop; } ;
typedef  TYPE_1__ MGSLPC_INFO ;

/* Variables and functions */

__attribute__((used)) static int mgslpc_suspend(struct pcmcia_device *link)
{
	MGSLPC_INFO *info = link->priv;

	info->stop = 1;

	return 0;
}