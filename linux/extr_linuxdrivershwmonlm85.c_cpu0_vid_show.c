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
struct lm85_data {int vid; int /*<<< orphan*/  vrm; scalar_t__ has_vid5; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct lm85_data* lm85_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int vid_from_reg (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t cpu0_vid_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	struct lm85_data *data = lm85_update_device(dev);
	int vid;

	if (data->has_vid5) {
		/* 6-pin VID (VRM 10) */
		vid = vid_from_reg(data->vid & 0x3f, data->vrm);
	} else {
		/* 5-pin VID (VRM 9) */
		vid = vid_from_reg(data->vid & 0x1f, data->vrm);
	}

	return sprintf(buf, "%d\n", vid);
}