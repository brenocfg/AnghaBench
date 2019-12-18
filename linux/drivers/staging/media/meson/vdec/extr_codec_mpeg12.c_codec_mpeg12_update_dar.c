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
typedef  int u32 ;
struct TYPE_2__ {int numerator; int denominator; } ;
struct amvdec_session {TYPE_1__ pixelaspect; struct amvdec_core* core; } ;
struct amvdec_core {int dummy; } ;

/* Variables and functions */
#define  MPEG2_DAR_16_9 130 
#define  MPEG2_DAR_221_100 129 
#define  MPEG2_DAR_4_3 128 
 int MPEG2_SEQ_DAR_MASK ; 
 int /*<<< orphan*/  MREG_SEQ_INFO ; 
 int amvdec_read_dos (struct amvdec_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amvdec_set_par_from_dar (struct amvdec_session*,int,int) ; 

__attribute__((used)) static void codec_mpeg12_update_dar(struct amvdec_session *sess)
{
	struct amvdec_core *core = sess->core;
	u32 seq = amvdec_read_dos(core, MREG_SEQ_INFO);
	u32 ar = seq & MPEG2_SEQ_DAR_MASK;

	switch (ar) {
	case MPEG2_DAR_4_3:
		amvdec_set_par_from_dar(sess, 4, 3);
		break;
	case MPEG2_DAR_16_9:
		amvdec_set_par_from_dar(sess, 16, 9);
		break;
	case MPEG2_DAR_221_100:
		amvdec_set_par_from_dar(sess, 221, 100);
		break;
	default:
		sess->pixelaspect.numerator = 1;
		sess->pixelaspect.denominator = 1;
		break;
	}
}