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
struct cx25821_dev {int /*<<< orphan*/ * lmmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cx25821_iounmap(struct cx25821_dev *dev)
{
	if (dev == NULL)
		return;

	/* Releasing IO memory */
	if (dev->lmmio != NULL) {
		iounmap(dev->lmmio);
		dev->lmmio = NULL;
	}
}