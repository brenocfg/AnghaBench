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
 scalar_t__ base ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int irq ; 

__attribute__((used)) static int pca_isa_match(struct device *dev, unsigned int id)
{
	int match = base != 0;

	if (match) {
		if (irq <= -1)
			dev_warn(dev, "Using polling mode (specify irq)\n");
	} else
		dev_err(dev, "Please specify I/O base\n");

	return match;
}