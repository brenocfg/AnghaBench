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
 int DVB_CA_EN50221_POLL_CAM_PRESENT ; 
 int DVB_CA_EN50221_POLL_CAM_READY ; 
 int EINVAL ; 
 int /*<<< orphan*/  TT3650_CMD_CI_TEST ; 
 int tt3650_ci_msg_locked (struct dvb_ca_en50221*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tt3650_ci_poll_slot_status(struct dvb_ca_en50221 *ca, int slot, int open)
{
	u8 buf[1];
	int ret;

	if (slot)
		return -EINVAL;

	ret = tt3650_ci_msg_locked(ca, TT3650_CMD_CI_TEST, buf, 0, 1);
	if (ret)
		return ret;

	if (1 == buf[0]) {
		return DVB_CA_EN50221_POLL_CAM_PRESENT |
			DVB_CA_EN50221_POLL_CAM_READY;
	}
	return 0;
}