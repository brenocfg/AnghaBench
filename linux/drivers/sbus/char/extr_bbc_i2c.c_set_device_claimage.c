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
struct TYPE_2__ {int client_claimed; struct platform_device* device; } ;

/* Variables and functions */
 int NUM_CHILDREN ; 

__attribute__((used)) static void set_device_claimage(struct bbc_i2c_bus *bp, struct platform_device *op, int val)
{
	int i;

	for (i = 0; i < NUM_CHILDREN; i++) {
		if (bp->devs[i].device == op) {
			bp->devs[i].client_claimed = val;
			return;
		}
	}
}