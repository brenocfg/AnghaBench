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
struct komeda_pipeline {int dummy; } ;
struct komeda_component {int dummy; } ;

/* Variables and functions */
 struct komeda_component** komeda_pipeline_get_component_pos (struct komeda_pipeline*,int) ; 

struct komeda_component *
komeda_pipeline_get_component(struct komeda_pipeline *pipe, int id)
{
	struct komeda_component **pos = NULL;
	struct komeda_component *c = NULL;

	pos = komeda_pipeline_get_component_pos(pipe, id);
	if (pos)
		c = *pos;

	return c;
}