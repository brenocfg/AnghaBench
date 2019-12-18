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
typedef  int /*<<< orphan*/  vop_header ;
typedef  size_t u8 ;
typedef  int u32 ;
struct solo_enc_dev {int dummy; } ;
struct solo_enc_buf {int motion; int /*<<< orphan*/  vh; int /*<<< orphan*/  type; } ;
struct solo_dev {size_t enc_idx; int /*<<< orphan*/  vh_buf; int /*<<< orphan*/  vh_dma; TYPE_1__* pdev; struct solo_enc_dev** v4l2_enc; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MP4_QS ; 
 int /*<<< orphan*/  SOLO_ENC_TYPE_EXT ; 
 int /*<<< orphan*/  SOLO_ENC_TYPE_STD ; 
 size_t SOLO_MAX_CHANNELS ; 
 scalar_t__ SOLO_MP4E_EXT_ADDR (struct solo_dev*) ; 
 int /*<<< orphan*/  SOLO_VE_MPEG4_QUE (size_t) ; 
 int /*<<< orphan*/  SOLO_VE_STATE (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t) ; 
 scalar_t__ enc_get_mpeg_dma (struct solo_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  solo_enc_handle_one (struct solo_enc_dev*,struct solo_enc_buf*) ; 
 scalar_t__ solo_motion_detected (struct solo_enc_dev*) ; 
 int solo_reg_read (struct solo_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ vop_mpeg_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void solo_handle_ring(struct solo_dev *solo_dev)
{
	for (;;) {
		struct solo_enc_dev *solo_enc;
		struct solo_enc_buf enc_buf;
		u32 mpeg_current, off;
		u8 ch;
		u8 cur_q;

		/* Check if the hardware has any new ones in the queue */
		cur_q = solo_reg_read(solo_dev, SOLO_VE_STATE(11)) & 0xff;
		if (cur_q == solo_dev->enc_idx)
			break;

		mpeg_current = solo_reg_read(solo_dev,
					SOLO_VE_MPEG4_QUE(solo_dev->enc_idx));
		solo_dev->enc_idx = (solo_dev->enc_idx + 1) % MP4_QS;

		ch = (mpeg_current >> 24) & 0x1f;
		off = mpeg_current & 0x00ffffff;

		if (ch >= SOLO_MAX_CHANNELS) {
			ch -= SOLO_MAX_CHANNELS;
			enc_buf.type = SOLO_ENC_TYPE_EXT;
		} else
			enc_buf.type = SOLO_ENC_TYPE_STD;

		solo_enc = solo_dev->v4l2_enc[ch];
		if (solo_enc == NULL) {
			dev_err(&solo_dev->pdev->dev,
				"Got spurious packet for channel %d\n", ch);
			continue;
		}

		/* FAIL... */
		if (enc_get_mpeg_dma(solo_dev, solo_dev->vh_dma, off,
				     sizeof(vop_header)))
			continue;

		enc_buf.vh = solo_dev->vh_buf;

		/* Sanity check */
		if (vop_mpeg_offset(enc_buf.vh) !=
			SOLO_MP4E_EXT_ADDR(solo_dev) + off)
			continue;

		if (solo_motion_detected(solo_enc))
			enc_buf.motion = 1;
		else
			enc_buf.motion = 0;

		solo_enc_handle_one(solo_enc, &enc_buf);
	}
}