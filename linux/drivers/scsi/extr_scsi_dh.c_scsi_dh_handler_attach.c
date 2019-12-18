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
struct scsi_device_handler {int (* attach ) (struct scsi_device*) ;int /*<<< orphan*/  module; int /*<<< orphan*/  name; } ;
struct scsi_device {struct scsi_device_handler* handler; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KERN_ERR ; 
#define  SCSI_DH_DEV_UNSUPP 131 
#define  SCSI_DH_NOMEM 130 
#define  SCSI_DH_NOSYS 129 
 int SCSI_DH_OK ; 
#define  SCSI_DH_RES_TEMP_UNAVAIL 128 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct scsi_device*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scsi_dh_handler_attach(struct scsi_device *sdev,
				  struct scsi_device_handler *scsi_dh)
{
	int error, ret = 0;

	if (!try_module_get(scsi_dh->module))
		return -EINVAL;

	error = scsi_dh->attach(sdev);
	if (error != SCSI_DH_OK) {
		switch (error) {
		case SCSI_DH_NOMEM:
			ret = -ENOMEM;
			break;
		case SCSI_DH_RES_TEMP_UNAVAIL:
			ret = -EAGAIN;
			break;
		case SCSI_DH_DEV_UNSUPP:
		case SCSI_DH_NOSYS:
			ret = -ENODEV;
			break;
		default:
			ret = -EINVAL;
			break;
		}
		if (ret != -ENODEV)
			sdev_printk(KERN_ERR, sdev, "%s: Attach failed (%d)\n",
				    scsi_dh->name, error);
		module_put(scsi_dh->module);
	} else
		sdev->handler = scsi_dh;

	return ret;
}