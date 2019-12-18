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
struct sm_ftl {int /*<<< orphan*/  mutex; } ;
struct mtd_blktrans_dev {struct sm_ftl* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sm_cache_flush (struct sm_ftl*) ; 

__attribute__((used)) static int sm_flush(struct mtd_blktrans_dev *dev)
{
	struct sm_ftl *ftl = dev->priv;
	int retval;

	mutex_lock(&ftl->mutex);
	retval =  sm_cache_flush(ftl);
	mutex_unlock(&ftl->mutex);
	return retval;
}