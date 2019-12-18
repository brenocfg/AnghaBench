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
typedef  int /*<<< orphan*/  uuid_le ;
typedef  int /*<<< orphan*/  u8 ;
struct mei_cl_device {int /*<<< orphan*/  name; int /*<<< orphan*/  me_cl; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/ * mei_me_cl_uuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_me_cl_ver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct mei_cl_device* to_mei_cl_device (struct device*) ; 

__attribute__((used)) static ssize_t modalias_show(struct device *dev, struct device_attribute *a,
			     char *buf)
{
	struct mei_cl_device *cldev = to_mei_cl_device(dev);
	const uuid_le *uuid = mei_me_cl_uuid(cldev->me_cl);
	u8 version = mei_me_cl_ver(cldev->me_cl);

	return scnprintf(buf, PAGE_SIZE, "mei:%s:%pUl:%02X:",
			 cldev->name, uuid, version);
}