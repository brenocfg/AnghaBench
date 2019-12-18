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
struct imgu_device {int dummy; } ;
struct TYPE_2__ {unsigned int css_queue; } ;

/* Variables and functions */
 unsigned int IMGU_NODE_NUM ; 
 TYPE_1__* imgu_node_map ; 

unsigned int imgu_map_node(struct imgu_device *imgu, unsigned int css_queue)
{
	unsigned int i;

	for (i = 0; i < IMGU_NODE_NUM; i++)
		if (imgu_node_map[i].css_queue == css_queue)
			break;

	return i;
}