#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {int chanl_space; } ;
struct TYPE_4__ {TYPE_1__ region; } ;
struct fmdev {TYPE_2__ rx; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 int /*<<< orphan*/  CHANL_BW_SET ; 
 int FM_CHANNEL_SPACING_100KHZ ; 
 int FM_CHANNEL_SPACING_200KHZ ; 
 int FM_CHANNEL_SPACING_50KHZ ; 
 int FM_FREQ_MUL ; 
 int /*<<< orphan*/  REG_WR ; 
 int fmc_send_cmd (struct fmdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fm_rx_set_channel_spacing(struct fmdev *fmdev, u32 spacing)
{
	u16 payload;
	int ret;

	if (spacing > 0 && spacing <= 50000)
		spacing = FM_CHANNEL_SPACING_50KHZ;
	else if (spacing > 50000 && spacing <= 100000)
		spacing = FM_CHANNEL_SPACING_100KHZ;
	else
		spacing = FM_CHANNEL_SPACING_200KHZ;

	/* set channel spacing */
	payload = spacing;
	ret = fmc_send_cmd(fmdev, CHANL_BW_SET, REG_WR, &payload,
			sizeof(payload), NULL, NULL);
	if (ret < 0)
		return ret;

	fmdev->rx.region.chanl_space = spacing * FM_FREQ_MUL;

	return ret;
}