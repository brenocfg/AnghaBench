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
struct wf_sensor {int /*<<< orphan*/  name; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wf_lock ; 
 int /*<<< orphan*/  wf_put_sensor (struct wf_sensor*) ; 

void wf_unregister_sensor(struct wf_sensor *sr)
{
	mutex_lock(&wf_lock);
	list_del(&sr->link);
	mutex_unlock(&wf_lock);

	DBG("wf: Unregistered sensor %s\n", sr->name);

	wf_put_sensor(sr);
}