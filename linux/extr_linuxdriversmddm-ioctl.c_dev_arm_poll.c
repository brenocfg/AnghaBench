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
struct file {struct dm_file* private_data; } ;
struct dm_ioctl {int dummy; } ;
struct dm_file {int /*<<< orphan*/  global_event_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_global_event_nr ; 

__attribute__((used)) static int dev_arm_poll(struct file *filp, struct dm_ioctl *param, size_t param_size)
{
	struct dm_file *priv = filp->private_data;

	priv->global_event_nr = atomic_read(&dm_global_event_nr);

	return 0;
}