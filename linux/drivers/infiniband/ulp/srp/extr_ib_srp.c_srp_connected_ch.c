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
struct srp_target_port {int ch_count; TYPE_1__* ch; } ;
struct TYPE_2__ {scalar_t__ connected; } ;

/* Variables and functions */

__attribute__((used)) static int srp_connected_ch(struct srp_target_port *target)
{
	int i, c = 0;

	for (i = 0; i < target->ch_count; i++)
		c += target->ch[i].connected;

	return c;
}