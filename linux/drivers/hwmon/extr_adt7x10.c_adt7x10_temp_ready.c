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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADT7X10_STATUS ; 
 int ADT7X10_STAT_NOT_RDY ; 
 int ETIMEDOUT ; 
 int adt7x10_read_byte (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int adt7x10_temp_ready(struct device *dev)
{
	int i, status;

	for (i = 0; i < 6; i++) {
		status = adt7x10_read_byte(dev, ADT7X10_STATUS);
		if (status < 0)
			return status;
		if (!(status & ADT7X10_STAT_NOT_RDY))
			return 0;
		msleep(60);
	}
	return -ETIMEDOUT;
}