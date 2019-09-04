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
struct scif_hw_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct scif_hw_dev* dev_to_scif (struct device*) ; 
 int /*<<< orphan*/  kfree (struct scif_hw_dev*) ; 

__attribute__((used)) static void scif_release_dev(struct device *d)
{
	struct scif_hw_dev *sdev = dev_to_scif(d);

	kfree(sdev);
}