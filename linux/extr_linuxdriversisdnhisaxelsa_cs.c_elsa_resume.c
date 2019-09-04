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
struct TYPE_2__ {scalar_t__ busy; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */

__attribute__((used)) static int elsa_resume(struct pcmcia_device *link)
{
	local_info_t *dev = link->priv;

	dev->busy = 0;

	return 0;
}