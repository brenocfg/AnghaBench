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
struct platform_device {int dummy; } ;
struct bbc_i2c_bus {TYPE_1__* devs; } ;
struct TYPE_2__ {struct platform_device* device; } ;

/* Variables and functions */
 int NUM_CHILDREN ; 

struct platform_device *bbc_i2c_getdev(struct bbc_i2c_bus *bp, int index)
{
	struct platform_device *op = NULL;
	int curidx = 0, i;

	for (i = 0; i < NUM_CHILDREN; i++) {
		if (!(op = bp->devs[i].device))
			break;
		if (curidx == index)
			goto out;
		op = NULL;
		curidx++;
	}

out:
	if (curidx == index)
		return op;
	return NULL;
}