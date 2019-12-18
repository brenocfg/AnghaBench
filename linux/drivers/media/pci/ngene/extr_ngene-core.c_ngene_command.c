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
struct ngene_command {int dummy; } ;
struct ngene {int /*<<< orphan*/  cmd_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ngene_command_mutex (struct ngene*,struct ngene_command*) ; 

int ngene_command(struct ngene *dev, struct ngene_command *com)
{
	int result;

	mutex_lock(&dev->cmd_mutex);
	result = ngene_command_mutex(dev, com);
	mutex_unlock(&dev->cmd_mutex);
	return result;
}