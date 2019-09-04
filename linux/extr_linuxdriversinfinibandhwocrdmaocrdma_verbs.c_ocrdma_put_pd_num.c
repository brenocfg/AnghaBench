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
typedef  int /*<<< orphan*/  u16 ;
struct ocrdma_dev {int /*<<< orphan*/  dev_lock; } ;

/* Variables and functions */
 int _ocrdma_pd_mgr_put_bitmap (struct ocrdma_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocrdma_put_pd_num(struct ocrdma_dev *dev, u16 pd_id,
				   bool dpp_pool)
{
	int status;

	mutex_lock(&dev->dev_lock);
	status = _ocrdma_pd_mgr_put_bitmap(dev, pd_id, dpp_pool);
	mutex_unlock(&dev->dev_lock);
	return status;
}