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
struct device {int /*<<< orphan*/  devt; } ;

/* Variables and functions */
 unsigned int MAJOR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int major_match(struct device *dev, const void *data)
{
	unsigned int major = *(unsigned int *)data;

	return MAJOR(dev->devt) == major;
}