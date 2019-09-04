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
typedef  int /*<<< orphan*/  u16 ;
struct fmdev {int dummy; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 int /*<<< orphan*/  MUTE ; 
 int /*<<< orphan*/  REG_WR ; 
 int fmc_send_cmd (struct fmdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmdbg (char*,int /*<<< orphan*/ ) ; 

int fm_tx_set_mute_mode(struct fmdev *fmdev, u8 mute_mode_toset)
{
	u16 payload;
	int ret;

	fmdbg("tx: mute mode %d\n", mute_mode_toset);

	payload = mute_mode_toset;
	ret = fmc_send_cmd(fmdev, MUTE, REG_WR, &payload,
			sizeof(payload), NULL, NULL);
	if (ret < 0)
		return ret;

	return 0;
}