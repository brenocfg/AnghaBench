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
struct xvip_pipeline {int /*<<< orphan*/ * output; scalar_t__ num_dmas; } ;

/* Variables and functions */

__attribute__((used)) static void __xvip_pipeline_cleanup(struct xvip_pipeline *pipe)
{
	pipe->num_dmas = 0;
	pipe->output = NULL;
}