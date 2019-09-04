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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fmdev {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  REG_RD ; 
 int /*<<< orphan*/  RSSI_LVL_GET ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int fmc_send_cmd (struct fmdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmerr (char*) ; 

int fm_rx_get_rssi_level(struct fmdev *fmdev, u16 *rssilvl)
{
	__be16 curr_rssi_lel;
	u32 resp_len;
	int ret;

	if (rssilvl == NULL) {
		fmerr("Invalid memory\n");
		return -ENOMEM;
	}
	/* Read current RSSI level */
	ret = fmc_send_cmd(fmdev, RSSI_LVL_GET, REG_RD, NULL, 2,
			&curr_rssi_lel, &resp_len);
	if (ret < 0)
		return ret;

	*rssilvl = be16_to_cpu(curr_rssi_lel);

	return 0;
}