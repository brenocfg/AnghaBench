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

/* Variables and functions */
 int NR_RSCS ; 
 int /*<<< orphan*/  crw_handler_mutex ; 
 int /*<<< orphan*/ ** crw_handlers ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void crw_unregister_handler(int rsc)
{
	if ((rsc < 0) || (rsc >= NR_RSCS))
		return;
	mutex_lock(&crw_handler_mutex);
	crw_handlers[rsc] = NULL;
	mutex_unlock(&crw_handler_mutex);
}