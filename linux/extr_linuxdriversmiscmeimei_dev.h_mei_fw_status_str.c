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
struct mei_fw_status {int dummy; } ;
struct mei_device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  MEI_FW_STATUS_STR_SZ ; 
 int mei_fw_status (struct mei_device*,struct mei_fw_status*) ; 
 int mei_fw_status2str (struct mei_fw_status*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline ssize_t mei_fw_status_str(struct mei_device *dev,
					char *buf, size_t len)
{
	struct mei_fw_status fw_status;
	int ret;

	buf[0] = '\0';

	ret = mei_fw_status(dev, &fw_status);
	if (ret)
		return ret;

	ret = mei_fw_status2str(&fw_status, buf, MEI_FW_STATUS_STR_SZ);

	return ret;
}