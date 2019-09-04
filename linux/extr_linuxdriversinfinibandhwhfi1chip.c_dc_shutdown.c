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
struct hfi1_devdata {int /*<<< orphan*/  dc8051_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dc_shutdown (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dc_shutdown(struct hfi1_devdata *dd)
{
	mutex_lock(&dd->dc8051_lock);
	_dc_shutdown(dd);
	mutex_unlock(&dd->dc8051_lock);
}