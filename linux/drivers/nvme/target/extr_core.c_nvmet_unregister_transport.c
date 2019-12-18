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
struct nvmet_fabrics_ops {size_t type; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_config_sem ; 
 int /*<<< orphan*/ ** nvmet_transports ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void nvmet_unregister_transport(const struct nvmet_fabrics_ops *ops)
{
	down_write(&nvmet_config_sem);
	nvmet_transports[ops->type] = NULL;
	up_write(&nvmet_config_sem);
}