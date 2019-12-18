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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct c2port_ops {int /*<<< orphan*/  (* c2d_dir ) (struct c2port_device*,int) ;int /*<<< orphan*/  (* access ) (struct c2port_device*,int) ;int /*<<< orphan*/  (* c2ck_set ) (struct c2port_device*,int) ;} ;
struct c2port_device {int access; int /*<<< orphan*/  mutex; struct c2port_ops* ops; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 struct c2port_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,int*) ; 
 int /*<<< orphan*/  stub1 (struct c2port_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct c2port_device*,int) ; 
 int /*<<< orphan*/  stub3 (struct c2port_device*,int) ; 

__attribute__((used)) static ssize_t access_store(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct c2port_device *c2dev = dev_get_drvdata(dev);
	struct c2port_ops *ops = c2dev->ops;
	int status, ret;

	ret = sscanf(buf, "%d", &status);
	if (ret != 1)
		return -EINVAL;

	mutex_lock(&c2dev->mutex);

	c2dev->access = !!status;

	/* If access is "on" clock should be HIGH _before_ setting the line
	 * as output and data line should be set as INPUT anyway */
	if (c2dev->access)
		ops->c2ck_set(c2dev, 1);
	ops->access(c2dev, c2dev->access);
	if (c2dev->access)
		ops->c2d_dir(c2dev, 1);

	mutex_unlock(&c2dev->mutex);

	return count;
}