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
struct komeda_pipeline {TYPE_1__* compiz; } ;
struct komeda_component {struct komeda_pipeline* pipeline; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOMEDA_PIPELINE_COMPIZS ; 
 struct komeda_component* komeda_component_pickup_input (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct komeda_pipeline *
komeda_pipeline_get_slave(struct komeda_pipeline *master)
{
	struct komeda_component *slave;

	slave = komeda_component_pickup_input(&master->compiz->base,
					      KOMEDA_PIPELINE_COMPIZS);

	return slave ? slave->pipeline : NULL;
}