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
struct file {struct ddb* private_data; } ;
struct ddb {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 long ENOTTY ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int,unsigned long) ; 

__attribute__((used)) static long ddb_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct ddb *dev = file->private_data;

	dev_warn(dev->dev, "DDB IOCTLs unsupported (cmd: %d, arg: %lu)\n",
		 cmd, arg);

	return -ENOTTY;
}