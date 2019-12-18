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
struct snd_device {struct go7007* device_data; } ;
struct go7007 {int /*<<< orphan*/ * snd_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int go7007_snd_free(struct snd_device *device)
{
	struct go7007 *go = device->device_data;

	kfree(go->snd_context);
	go->snd_context = NULL;
	return 0;
}