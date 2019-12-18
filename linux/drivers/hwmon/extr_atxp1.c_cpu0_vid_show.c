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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int vid; } ;
struct atxp1_data {int /*<<< orphan*/  vrm; TYPE_1__ reg; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ATXP1_VIDMASK ; 
 struct atxp1_data* atxp1_update_device (struct device*) ; 
 int sprintf (char*,char*,int) ; 
 int vid_from_reg (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t cpu0_vid_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	int size;
	struct atxp1_data *data;

	data = atxp1_update_device(dev);

	size = sprintf(buf, "%d\n", vid_from_reg(data->reg.vid & ATXP1_VIDMASK,
						 data->vrm));

	return size;
}