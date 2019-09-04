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
struct macio_dev {int n_resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  macio_release_resource (struct macio_dev*,int) ; 

void macio_release_resources(struct macio_dev *dev)
{
	int i;
	
	for (i = 0; i < dev->n_resources; i++)
		macio_release_resource(dev, i);
}