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
typedef  int /*<<< orphan*/  u32 ;
struct mei_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ mei_txe_aliveness_set (struct mei_device*,int /*<<< orphan*/ ) ; 
 int mei_txe_aliveness_wait (struct mei_device*,int /*<<< orphan*/ ) ; 

int mei_txe_aliveness_set_sync(struct mei_device *dev, u32 req)
{
	if (mei_txe_aliveness_set(dev, req))
		return mei_txe_aliveness_wait(dev, req);
	return 0;
}