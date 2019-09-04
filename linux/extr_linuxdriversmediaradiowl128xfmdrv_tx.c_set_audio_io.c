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
typedef  int /*<<< orphan*/  u16 ;
struct fmtx_data {int /*<<< orphan*/  audio_io; } ;
struct fmdev {struct fmtx_data tx_data; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_IO_SET ; 
 int /*<<< orphan*/  REG_WR ; 
 int fmc_send_cmd (struct fmdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_audio_io(struct fmdev *fmdev)
{
	struct fmtx_data *tx = &fmdev->tx_data;
	u16 payload;
	int ret;

	/* Set Audio I/O Enable */
	payload = tx->audio_io;
	ret = fmc_send_cmd(fmdev, AUDIO_IO_SET, REG_WR, &payload,
			sizeof(payload), NULL, NULL);
	if (ret < 0)
		return ret;

	/* TODO: is audio set? */
	return 0;
}