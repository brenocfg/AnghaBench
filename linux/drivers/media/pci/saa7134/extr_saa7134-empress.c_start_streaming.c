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
typedef  int u32 ;
struct vb2_queue {struct saa7134_dmaqueue* drv_priv; } ;
struct saa7134_dmaqueue {struct saa7134_dev* dev; } ;
struct saa7134_dev {int board; int empress_started; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_AUDIO_MUTE_CTRL ; 
#define  SAA7134_BOARD_BEHOLD_M6 130 
#define  SAA7134_BOARD_BEHOLD_M63 129 
#define  SAA7134_BOARD_BEHOLD_M6_EXTRA 128 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  init ; 
 int saa7134_ts_start_streaming (struct vb2_queue*,unsigned int) ; 
 int /*<<< orphan*/  saa_call_all (struct saa7134_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int saa_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct saa7134_dmaqueue *dmaq = vq->drv_priv;
	struct saa7134_dev *dev = dmaq->dev;
	u32 leading_null_bytes = 0;
	int err;

	err = saa7134_ts_start_streaming(vq, count);
	if (err)
		return err;

	/* If more cards start to need this, then this
	   should probably be added to the card definitions. */
	switch (dev->board) {
	case SAA7134_BOARD_BEHOLD_M6:
	case SAA7134_BOARD_BEHOLD_M63:
	case SAA7134_BOARD_BEHOLD_M6_EXTRA:
		leading_null_bytes = 1;
		break;
	}
	saa_call_all(dev, core, init, leading_null_bytes);
	/* Unmute audio */
	saa_writeb(SAA7134_AUDIO_MUTE_CTRL,
			saa_readb(SAA7134_AUDIO_MUTE_CTRL) & ~(1 << 6));
	dev->empress_started = 1;
	return 0;
}