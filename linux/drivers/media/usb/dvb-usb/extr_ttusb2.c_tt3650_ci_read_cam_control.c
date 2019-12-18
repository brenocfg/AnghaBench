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
typedef  int u8 ;
struct dvb_ca_en50221 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TT3650_CMD_CI_RD_CTRL ; 
 int /*<<< orphan*/  ci_dbg (char*,int,int,int) ; 
 int tt3650_ci_msg_locked (struct dvb_ca_en50221*,int /*<<< orphan*/ ,int*,int,int) ; 

__attribute__((used)) static int tt3650_ci_read_cam_control(struct dvb_ca_en50221 *ca, int slot, u8 address)
{
	u8 buf[2];
	int ret;

	if (slot)
		return -EINVAL;

	buf[0] = address & 3;

	ret = tt3650_ci_msg_locked(ca, TT3650_CMD_CI_RD_CTRL, buf, 1, 2);

	ci_dbg("0x%02x -> %d 0x%02x", address, ret, buf[1]);

	if (ret < 0)
		return ret;

	return buf[1];
}