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
typedef  int /*<<< orphan*/  u8 ;
struct mei_msg_hdr {int dummy; } ;
struct mei_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  hbm_f_pg_supported; } ;
struct hbm_power_gate {int /*<<< orphan*/  hbm_cmd; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mei_hbm_hdr (struct mei_msg_hdr*,size_t const) ; 
 int mei_hbm_write_message (struct mei_device*,struct mei_msg_hdr*,struct hbm_power_gate*) ; 
 int /*<<< orphan*/  memset (struct hbm_power_gate*,int /*<<< orphan*/ ,size_t const) ; 

int mei_hbm_pg(struct mei_device *dev, u8 pg_cmd)
{
	struct mei_msg_hdr mei_hdr;
	struct hbm_power_gate req;
	const size_t len = sizeof(struct hbm_power_gate);
	int ret;

	if (!dev->hbm_f_pg_supported)
		return -EOPNOTSUPP;

	mei_hbm_hdr(&mei_hdr, len);

	memset(&req, 0, len);
	req.hbm_cmd = pg_cmd;

	ret = mei_hbm_write_message(dev, &mei_hdr, &req);
	if (ret)
		dev_err(dev->dev, "power gate command write failed.\n");
	return ret;
}