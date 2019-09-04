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
struct hidpp_ff_private_data {int /*<<< orphan*/  effect_ids; } ;
struct ff_device {struct hidpp_ff_private_data* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hidpp_ff_destroy(struct ff_device *ff)
{
	struct hidpp_ff_private_data *data = ff->private;

	kfree(data->effect_ids);
}