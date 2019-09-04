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
struct saa7146_dev {scalar_t__ ext_priv; } ;
struct hexium {int /*<<< orphan*/  i2c_adapter; int /*<<< orphan*/  video_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_EE (char*,struct saa7146_dev*) ; 
 int /*<<< orphan*/  hexium_num ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hexium*) ; 
 int /*<<< orphan*/  saa7146_unregister_device (int /*<<< orphan*/ *,struct saa7146_dev*) ; 
 int /*<<< orphan*/  saa7146_vv_release (struct saa7146_dev*) ; 

__attribute__((used)) static int hexium_detach(struct saa7146_dev *dev)
{
	struct hexium *hexium = (struct hexium *) dev->ext_priv;

	DEB_EE("dev:%p\n", dev);

	saa7146_unregister_device(&hexium->video_dev, dev);
	saa7146_vv_release(dev);

	hexium_num--;

	i2c_del_adapter(&hexium->i2c_adapter);
	kfree(hexium);
	return 0;
}