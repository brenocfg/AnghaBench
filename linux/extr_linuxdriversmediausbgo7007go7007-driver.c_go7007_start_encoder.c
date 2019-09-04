#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct go7007 {int modet_enable; size_t* modet_map; int height; int width; int /*<<< orphan*/  v4l2_dev; scalar_t__ seen_frame; scalar_t__ parse_length; int /*<<< orphan*/  state; scalar_t__ dvd_mode; TYPE_1__* modet; int /*<<< orphan*/  modet_mode; } ;
struct TYPE_2__ {int enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_DATA ; 
#define  V4L2_DETECT_MD_MODE_GLOBAL 129 
#define  V4L2_DETECT_MD_MODE_REGION_GRID 128 
 scalar_t__ go7007_construct_fw_image (struct go7007*,int /*<<< orphan*/ **,int*) ; 
 scalar_t__ go7007_read_interrupt (struct go7007*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ go7007_send_firmware (struct go7007*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ go7007_stream_start (struct go7007*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 
 int v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 

int go7007_start_encoder(struct go7007 *go)
{
	u8 *fw;
	int fw_len, rv = 0, i, x, y;
	u16 intr_val, intr_data;

	go->modet_enable = 0;
	for (i = 0; i < 4; i++)
		go->modet[i].enable = 0;

	switch (v4l2_ctrl_g_ctrl(go->modet_mode)) {
	case V4L2_DETECT_MD_MODE_GLOBAL:
		memset(go->modet_map, 0, sizeof(go->modet_map));
		go->modet[0].enable = 1;
		go->modet_enable = 1;
		break;
	case V4L2_DETECT_MD_MODE_REGION_GRID:
		for (y = 0; y < go->height / 16; y++) {
			for (x = 0; x < go->width / 16; x++) {
				int idx = y * go->width / 16 + x;

				go->modet[go->modet_map[idx]].enable = 1;
			}
		}
		go->modet_enable = 1;
		break;
	}

	if (go->dvd_mode)
		go->modet_enable = 0;

	if (go7007_construct_fw_image(go, &fw, &fw_len) < 0)
		return -1;

	if (go7007_send_firmware(go, fw, fw_len) < 0 ||
			go7007_read_interrupt(go, &intr_val, &intr_data) < 0) {
		v4l2_err(&go->v4l2_dev, "error transferring firmware\n");
		rv = -1;
		goto start_error;
	}

	go->state = STATE_DATA;
	go->parse_length = 0;
	go->seen_frame = 0;
	if (go7007_stream_start(go) < 0) {
		v4l2_err(&go->v4l2_dev, "error starting stream transfer\n");
		rv = -1;
		goto start_error;
	}

start_error:
	kfree(fw);
	return rv;
}