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
struct ipmi_smi_watcher {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smi_watchers_mutex ; 

int ipmi_smi_watcher_unregister(struct ipmi_smi_watcher *watcher)
{
	mutex_lock(&smi_watchers_mutex);
	list_del(&watcher->link);
	mutex_unlock(&smi_watchers_mutex);
	return 0;
}