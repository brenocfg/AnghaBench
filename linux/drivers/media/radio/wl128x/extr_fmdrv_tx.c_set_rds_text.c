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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct fmdev {int dummy; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY_MODE ; 
 int /*<<< orphan*/  RDS_DATA_SET ; 
 int /*<<< orphan*/  REG_WR ; 
 int fmc_send_cmd (struct fmdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int strlen (scalar_t__*) ; 

__attribute__((used)) static int set_rds_text(struct fmdev *fmdev, u8 *rds_text)
{
	u16 payload;
	int ret;

	ret = fmc_send_cmd(fmdev, RDS_DATA_SET, REG_WR, rds_text,
			strlen(rds_text), NULL, NULL);
	if (ret < 0)
		return ret;

	/* Scroll mode */
	payload = (u16)0x1;
	ret = fmc_send_cmd(fmdev, DISPLAY_MODE, REG_WR, &payload,
			sizeof(payload), NULL, NULL);
	if (ret < 0)
		return ret;

	return 0;
}