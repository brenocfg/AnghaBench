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
typedef  size_t u8 ;
struct genwqe_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (char**) ; 
 struct genwqe_dev* dev_get_drvdata (struct device*) ; 
 size_t genwqe_card_type (struct genwqe_dev*) ; 
 char** genwqe_types ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t type_show(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	u8 card_type;
	struct genwqe_dev *cd = dev_get_drvdata(dev);

	card_type = genwqe_card_type(cd);
	return sprintf(buf, "%s\n", (card_type >= ARRAY_SIZE(genwqe_types)) ?
		       "invalid" : genwqe_types[card_type]);
}