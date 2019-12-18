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
struct ipu_di {int inuse; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipu_di_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ipu_di_put(struct ipu_di *di)
{
	mutex_lock(&ipu_di_lock);

	di->inuse = false;

	mutex_unlock(&ipu_di_lock);
}