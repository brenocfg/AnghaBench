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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct saa711x_state {scalar_t__ ident; struct v4l2_subdev sd; } ;
struct saa7115_platform_data {int* saa7113_r08_htc; int* saa7113_r10_ofts; int* saa7113_r12_rts0; int* saa7113_r12_rts1; scalar_t__* saa7113_r13_adlsb; scalar_t__* saa7113_r10_vrln; } ;

/* Variables and functions */
 scalar_t__ GM7113C ; 
 int /*<<< orphan*/  R_08_SYNC_CNTL ; 
 int /*<<< orphan*/  R_10_CHROMA_CNTL_2 ; 
 int /*<<< orphan*/  R_12_RT_SIGNAL_CNTL ; 
 int /*<<< orphan*/  R_13_RT_X_PORT_OUT_CNTL ; 
 scalar_t__ SAA7113 ; 
 int SAA7113_RTS_DOT_IN ; 
 int SAA7113_R_08_HTC_MASK ; 
 int SAA7113_R_08_HTC_OFFSET ; 
 int SAA7113_R_10_OFTS_MASK ; 
 int SAA7113_R_10_OFTS_OFFSET ; 
 int SAA7113_R_10_VRLN_MASK ; 
 int SAA7113_R_10_VRLN_OFFSET ; 
 int SAA7113_R_12_RTS0_MASK ; 
 int SAA7113_R_12_RTS0_OFFSET ; 
 int SAA7113_R_12_RTS1_MASK ; 
 int SAA7113_R_12_RTS1_OFFSET ; 
 int SAA7113_R_13_ADLSB_MASK ; 
 int SAA7113_R_13_ADLSB_OFFSET ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int saa711x_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa711x_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void saa711x_write_platform_data(struct saa711x_state *state,
					struct saa7115_platform_data *data)
{
	struct v4l2_subdev *sd = &state->sd;
	u8 work;

	if (state->ident != GM7113C &&
	    state->ident != SAA7113)
		return;

	if (data->saa7113_r08_htc) {
		work = saa711x_read(sd, R_08_SYNC_CNTL);
		work &= ~SAA7113_R_08_HTC_MASK;
		work |= ((*data->saa7113_r08_htc) << SAA7113_R_08_HTC_OFFSET);
		saa711x_write(sd, R_08_SYNC_CNTL, work);
	}

	if (data->saa7113_r10_vrln) {
		work = saa711x_read(sd, R_10_CHROMA_CNTL_2);
		work &= ~SAA7113_R_10_VRLN_MASK;
		if (*data->saa7113_r10_vrln)
			work |= (1 << SAA7113_R_10_VRLN_OFFSET);
		saa711x_write(sd, R_10_CHROMA_CNTL_2, work);
	}

	if (data->saa7113_r10_ofts) {
		work = saa711x_read(sd, R_10_CHROMA_CNTL_2);
		work &= ~SAA7113_R_10_OFTS_MASK;
		work |= (*data->saa7113_r10_ofts << SAA7113_R_10_OFTS_OFFSET);
		saa711x_write(sd, R_10_CHROMA_CNTL_2, work);
	}

	if (data->saa7113_r12_rts0) {
		work = saa711x_read(sd, R_12_RT_SIGNAL_CNTL);
		work &= ~SAA7113_R_12_RTS0_MASK;
		work |= (*data->saa7113_r12_rts0 << SAA7113_R_12_RTS0_OFFSET);

		/* According to the datasheet,
		 * SAA7113_RTS_DOT_IN should only be used on RTS1 */
		WARN_ON(*data->saa7113_r12_rts0 == SAA7113_RTS_DOT_IN);
		saa711x_write(sd, R_12_RT_SIGNAL_CNTL, work);
	}

	if (data->saa7113_r12_rts1) {
		work = saa711x_read(sd, R_12_RT_SIGNAL_CNTL);
		work &= ~SAA7113_R_12_RTS1_MASK;
		work |= (*data->saa7113_r12_rts1 << SAA7113_R_12_RTS1_OFFSET);
		saa711x_write(sd, R_12_RT_SIGNAL_CNTL, work);
	}

	if (data->saa7113_r13_adlsb) {
		work = saa711x_read(sd, R_13_RT_X_PORT_OUT_CNTL);
		work &= ~SAA7113_R_13_ADLSB_MASK;
		if (*data->saa7113_r13_adlsb)
			work |= (1 << SAA7113_R_13_ADLSB_OFFSET);
		saa711x_write(sd, R_13_RT_X_PORT_OUT_CNTL, work);
	}
}