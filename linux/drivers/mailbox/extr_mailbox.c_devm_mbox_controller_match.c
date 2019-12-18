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
typedef  void mbox_controller ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static int devm_mbox_controller_match(struct device *dev, void *res, void *data)
{
	struct mbox_controller **mbox = res;

	if (WARN_ON(!mbox || !*mbox))
		return 0;

	return *mbox == data;
}