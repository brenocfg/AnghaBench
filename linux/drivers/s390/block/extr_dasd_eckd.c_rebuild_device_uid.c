#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * cpaddr; } ;
struct path_verification_work_data {TYPE_1__ rcd_buffer; TYPE_1__ cqr; int /*<<< orphan*/  ccw; } ;
struct dasd_eckd_private {int /*<<< orphan*/  conf_data; } ;
struct dasd_device {int /*<<< orphan*/  cdev; struct dasd_eckd_private* private; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_ECKD_RCD_DATA_SIZE ; 
 int /*<<< orphan*/  DBF_EVENT_DEVID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int dasd_eckd_generate_uid (struct dasd_device*) ; 
 scalar_t__ dasd_eckd_identify_conf_parts (struct dasd_eckd_private*) ; 
 int dasd_eckd_read_conf_immediately (struct dasd_device*,TYPE_1__*,TYPE_1__,int) ; 
 int dasd_path_get_opm (struct dasd_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rebuild_device_uid(struct dasd_device *device,
			      struct path_verification_work_data *data)
{
	struct dasd_eckd_private *private = device->private;
	__u8 lpm, opm = dasd_path_get_opm(device);
	int rc = -ENODEV;

	for (lpm = 0x80; lpm; lpm >>= 1) {
		if (!(lpm & opm))
			continue;
		memset(&data->rcd_buffer, 0, sizeof(data->rcd_buffer));
		memset(&data->cqr, 0, sizeof(data->cqr));
		data->cqr.cpaddr = &data->ccw;
		rc = dasd_eckd_read_conf_immediately(device, &data->cqr,
						     data->rcd_buffer,
						     lpm);

		if (rc) {
			if (rc == -EOPNOTSUPP) /* -EOPNOTSUPP is ok */
				continue;
			DBF_EVENT_DEVID(DBF_WARNING, device->cdev,
					"Read configuration data "
					"returned error %d", rc);
			break;
		}
		memcpy(private->conf_data, data->rcd_buffer,
		       DASD_ECKD_RCD_DATA_SIZE);
		if (dasd_eckd_identify_conf_parts(private)) {
			rc = -ENODEV;
		} else /* first valid path is enough */
			break;
	}

	if (!rc)
		rc = dasd_eckd_generate_uid(device);

	return rc;
}