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
struct saa7134_dev {scalar_t__ ovenable; } ;

/* Variables and functions */
 int /*<<< orphan*/  saa7134_set_dmabits (struct saa7134_dev*) ; 

__attribute__((used)) static int stop_preview(struct saa7134_dev *dev)
{
	dev->ovenable = 0;
	saa7134_set_dmabits(dev);
	return 0;
}