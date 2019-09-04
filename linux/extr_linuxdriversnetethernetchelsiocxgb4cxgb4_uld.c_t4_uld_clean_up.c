#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct adapter {TYPE_1__* uld; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 unsigned int CXGB4_ULD_MAX ; 
 int /*<<< orphan*/  cxgb4_shutdown_uld_adapter (struct adapter*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uld_mutex ; 

void t4_uld_clean_up(struct adapter *adap)
{
	unsigned int i;

	mutex_lock(&uld_mutex);
	for (i = 0; i < CXGB4_ULD_MAX; i++) {
		if (!adap->uld[i].handle)
			continue;

		cxgb4_shutdown_uld_adapter(adap, i);
	}
	mutex_unlock(&uld_mutex);
}