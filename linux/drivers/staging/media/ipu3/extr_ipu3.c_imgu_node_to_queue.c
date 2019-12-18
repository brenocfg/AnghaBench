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
struct TYPE_2__ {unsigned int css_queue; } ;

/* Variables and functions */
 TYPE_1__* imgu_node_map ; 

unsigned int imgu_node_to_queue(unsigned int node)
{
	return imgu_node_map[node].css_queue;
}