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
struct saa7134_dev {int automute; } ;

/* Variables and functions */

int saa7134_tvaudio_close(struct saa7134_dev *dev)
{
	dev->automute = 1;
	/* anything else to undo? */
	return 0;
}