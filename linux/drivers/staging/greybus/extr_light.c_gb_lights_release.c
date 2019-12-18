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
struct gb_lights {int lights_count; int /*<<< orphan*/  lights_lock; struct gb_lights* lights; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_lights_light_release (struct gb_lights*) ; 
 int /*<<< orphan*/  kfree (struct gb_lights*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gb_lights_release(struct gb_lights *glights)
{
	int i;

	if (!glights)
		return;

	mutex_lock(&glights->lights_lock);
	if (!glights->lights)
		goto free_glights;

	for (i = 0; i < glights->lights_count; i++)
		gb_lights_light_release(&glights->lights[i]);

	kfree(glights->lights);

free_glights:
	mutex_unlock(&glights->lights_lock);
	mutex_destroy(&glights->lights_lock);
	kfree(glights);
}