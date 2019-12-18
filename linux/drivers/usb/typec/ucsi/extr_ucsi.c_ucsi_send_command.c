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
struct ucsi_control {int dummy; } ;
struct ucsi {int /*<<< orphan*/  ppm_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ucsi_run_command (struct ucsi*,struct ucsi_control*,void*,size_t) ; 

int ucsi_send_command(struct ucsi *ucsi, struct ucsi_control *ctrl,
		      void *retval, size_t size)
{
	int ret;

	mutex_lock(&ucsi->ppm_lock);
	ret = ucsi_run_command(ucsi, ctrl, retval, size);
	mutex_unlock(&ucsi->ppm_lock);

	return ret;
}