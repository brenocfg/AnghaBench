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
typedef  int /*<<< orphan*/  u32 ;
struct komeda_pipeline {int dummy; } ;
struct komeda_component {int dummy; } ;

/* Variables and functions */
 int find_first_bit (unsigned long*,int) ; 
 struct komeda_component* komeda_pipeline_get_component (struct komeda_pipeline*,int) ; 

struct komeda_component *
komeda_pipeline_get_first_component(struct komeda_pipeline *pipe,
				    u32 comp_mask)
{
	struct komeda_component *c = NULL;
	int id;

	id = find_first_bit((unsigned long *)&comp_mask, 32);
	if (id < 32)
		c = komeda_pipeline_get_component(pipe, id);

	return c;
}