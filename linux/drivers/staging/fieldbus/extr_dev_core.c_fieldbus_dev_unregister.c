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
struct fieldbus_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fieldbus_dev_unregister (struct fieldbus_dev*) ; 
 int /*<<< orphan*/  fieldbus_mtx ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void fieldbus_dev_unregister(struct fieldbus_dev *fb)
{
	mutex_lock(&fieldbus_mtx);
	__fieldbus_dev_unregister(fb);
	mutex_unlock(&fieldbus_mtx);
}