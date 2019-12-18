#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct da903x_chip {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_status ) (struct da903x_chip*,unsigned int*) ;} ;

/* Variables and functions */
 struct da903x_chip* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct da903x_chip*,unsigned int*) ; 

int da903x_query_status(struct device *dev, unsigned int sbits)
{
	struct da903x_chip *chip = dev_get_drvdata(dev);
	unsigned int status = 0;

	chip->ops->read_status(chip, &status);
	return ((status & sbits) == sbits);
}