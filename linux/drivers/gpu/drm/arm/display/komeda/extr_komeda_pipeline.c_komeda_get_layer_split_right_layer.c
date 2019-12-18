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
struct komeda_pipeline {int n_layers; struct komeda_layer** layers; } ;
struct TYPE_2__ {int id; } ;
struct komeda_layer {scalar_t__ layer_type; TYPE_1__ base; } ;

/* Variables and functions */
 int KOMEDA_COMPONENT_LAYER0 ; 

__attribute__((used)) static struct komeda_layer *
komeda_get_layer_split_right_layer(struct komeda_pipeline *pipe,
				   struct komeda_layer *left)
{
	int index = left->base.id - KOMEDA_COMPONENT_LAYER0;
	int i;

	for (i = index + 1; i < pipe->n_layers; i++)
		if (left->layer_type == pipe->layers[i]->layer_type)
			return pipe->layers[i];
	return NULL;
}