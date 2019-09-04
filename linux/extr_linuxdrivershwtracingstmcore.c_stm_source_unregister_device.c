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
struct stm_source_device {int /*<<< orphan*/  dev; } ;
struct stm_source_data {struct stm_source_device* src; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm_source_link_drop (struct stm_source_device*) ; 

void stm_source_unregister_device(struct stm_source_data *data)
{
	struct stm_source_device *src = data->src;

	stm_source_link_drop(src);

	device_unregister(&src->dev);
}