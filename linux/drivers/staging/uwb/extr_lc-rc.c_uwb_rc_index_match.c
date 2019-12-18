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
struct uwb_rc {int const index; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct uwb_rc* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int uwb_rc_index_match(struct device *dev, const void *data)
{
	const int *index = data;
	struct uwb_rc *rc = dev_get_drvdata(dev);

	if (rc->index == *index)
		return 1;
	return 0;
}