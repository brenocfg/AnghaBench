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
struct saa7134_dev {int /*<<< orphan*/ * input_ent; } ;

/* Variables and functions */
 int SAA7134_INPUT_MAX ; 
 int /*<<< orphan*/  media_device_unregister_entity (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void saa7134_media_release(struct saa7134_dev *dev)
{
#ifdef CONFIG_MEDIA_CONTROLLER
	int i;

	for (i = 0; i < SAA7134_INPUT_MAX + 1; i++)
		media_device_unregister_entity(&dev->input_ent[i]);
#endif
}