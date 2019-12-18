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
struct comedi_device {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_dev_kref_release ; 
 int kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int comedi_dev_put(struct comedi_device *dev)
{
	if (dev)
		return kref_put(&dev->refcount, comedi_dev_kref_release);
	return 1;
}