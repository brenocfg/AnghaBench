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
struct panfrost_file_priv {int /*<<< orphan*/ * sched_entity; } ;

/* Variables and functions */
 int NUM_JOB_SLOTS ; 
 int /*<<< orphan*/  drm_sched_entity_destroy (int /*<<< orphan*/ *) ; 

void panfrost_job_close(struct panfrost_file_priv *panfrost_priv)
{
	int i;

	for (i = 0; i < NUM_JOB_SLOTS; i++)
		drm_sched_entity_destroy(&panfrost_priv->sched_entity[i]);
}