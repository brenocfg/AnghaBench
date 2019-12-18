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
struct ipack {struct av7110* data; } ;
struct av7110 {int /*<<< orphan*/ ** kbuf; scalar_t__ iobuf; int /*<<< orphan*/  aout; int /*<<< orphan*/  avout; struct ipack* ipack; } ;

/* Variables and functions */
 scalar_t__ AOUTLEN ; 
 scalar_t__ AVOUTLEN ; 
 scalar_t__ BMPLEN ; 
 int IPACKS ; 
 int /*<<< orphan*/  av7110_ipack_free (struct ipack*) ; 
 int av7110_ipack_init (struct ipack*,int,void (*) (u8*,int,void*)) ; 
 int /*<<< orphan*/  dvb_ringbuffer_init (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  play_audio_cb ; 
 int /*<<< orphan*/  play_video_cb ; 

int av7110_av_init(struct av7110 *av7110)
{
	void (*play[])(u8 *, int, void *) = { play_audio_cb, play_video_cb };
	int i, ret;

	for (i = 0; i < 2; i++) {
		struct ipack *ipack = av7110->ipack + i;

		ret = av7110_ipack_init(ipack, IPACKS, play[i]);
		if (ret < 0) {
			if (i)
				av7110_ipack_free(--ipack);
			goto out;
		}
		ipack->data = av7110;
	}

	dvb_ringbuffer_init(&av7110->avout, av7110->iobuf, AVOUTLEN);
	dvb_ringbuffer_init(&av7110->aout, av7110->iobuf + AVOUTLEN, AOUTLEN);

	av7110->kbuf[0] = (u8 *)(av7110->iobuf + AVOUTLEN + AOUTLEN + BMPLEN);
	av7110->kbuf[1] = av7110->kbuf[0] + 2 * IPACKS;
out:
	return ret;
}