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
struct coda_dev {TYPE_1__* devtype; int /*<<< orphan*/  instance_mask; } ;
struct TYPE_2__ {scalar_t__ product; } ;

/* Variables and functions */
 int CODADX6_MAX_INSTANCES ; 
 scalar_t__ CODA_DX6 ; 
 int EBUSY ; 
 int ffz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int coda_next_free_instance(struct coda_dev *dev)
{
	int idx = ffz(dev->instance_mask);

	if ((idx < 0) ||
	    (dev->devtype->product == CODA_DX6 && idx > CODADX6_MAX_INSTANCES))
		return -EBUSY;

	return idx;
}