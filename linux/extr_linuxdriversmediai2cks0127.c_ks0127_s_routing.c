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
struct v4l2_subdev {int dummy; } ;
struct ks0127 {int norm; } ;

/* Variables and functions */
 size_t KS_BRT ; 
 size_t KS_CHROMB ; 
 size_t KS_CMDA ; 
 size_t KS_CMDB ; 
 size_t KS_CMDC ; 
 size_t KS_CMDD ; 
 size_t KS_CON ; 
 size_t KS_CTRACK ; 
 size_t KS_DEMOD ; 
 size_t KS_HUE ; 
#define  KS_INPUT_COMPOSITE_1 137 
#define  KS_INPUT_COMPOSITE_2 136 
#define  KS_INPUT_COMPOSITE_3 135 
#define  KS_INPUT_COMPOSITE_4 134 
#define  KS_INPUT_COMPOSITE_5 133 
#define  KS_INPUT_COMPOSITE_6 132 
#define  KS_INPUT_SVIDEO_1 131 
#define  KS_INPUT_SVIDEO_2 130 
#define  KS_INPUT_SVIDEO_3 129 
#define  KS_INPUT_YUV656 128 
 size_t KS_LUMA ; 
 size_t KS_SAT ; 
 size_t KS_UGAIN ; 
 size_t KS_UVOFFH ; 
 size_t KS_UVOFFL ; 
 size_t KS_VERTIA ; 
 size_t KS_VERTIC ; 
 size_t KS_VGAIN ; 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  ks0127_and_or (struct v4l2_subdev*,size_t,int,int) ; 
 int /*<<< orphan*/  ks0127_write (struct v4l2_subdev*,size_t,int) ; 
 int* reg_defaults ; 
 struct ks0127* to_ks0127 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,...) ; 

__attribute__((used)) static int ks0127_s_routing(struct v4l2_subdev *sd,
			    u32 input, u32 output, u32 config)
{
	struct ks0127 *ks = to_ks0127(sd);

	switch (input) {
	case KS_INPUT_COMPOSITE_1:
	case KS_INPUT_COMPOSITE_2:
	case KS_INPUT_COMPOSITE_3:
	case KS_INPUT_COMPOSITE_4:
	case KS_INPUT_COMPOSITE_5:
	case KS_INPUT_COMPOSITE_6:
		v4l2_dbg(1, debug, sd,
			"s_routing %d: Composite\n", input);
		/* autodetect 50/60 Hz */
		ks0127_and_or(sd, KS_CMDA,   0xfc, 0x00);
		/* VSE=0 */
		ks0127_and_or(sd, KS_CMDA,   ~0x40, 0x00);
		/* set input line */
		ks0127_and_or(sd, KS_CMDB,   0xb0, input);
		/* non-freerunning mode */
		ks0127_and_or(sd, KS_CMDC,   0x70, 0x0a);
		/* analog input */
		ks0127_and_or(sd, KS_CMDD,   0x03, 0x00);
		/* enable chroma demodulation */
		ks0127_and_or(sd, KS_CTRACK, 0xcf, 0x00);
		/* chroma trap, HYBWR=1 */
		ks0127_and_or(sd, KS_LUMA,   0x00,
			       (reg_defaults[KS_LUMA])|0x0c);
		/* scaler fullbw, luma comb off */
		ks0127_and_or(sd, KS_VERTIA, 0x08, 0x81);
		/* manual chroma comb .25 .5 .25 */
		ks0127_and_or(sd, KS_VERTIC, 0x0f, 0x90);

		/* chroma path delay */
		ks0127_and_or(sd, KS_CHROMB, 0x0f, 0x90);

		ks0127_write(sd, KS_UGAIN, reg_defaults[KS_UGAIN]);
		ks0127_write(sd, KS_VGAIN, reg_defaults[KS_VGAIN]);
		ks0127_write(sd, KS_UVOFFH, reg_defaults[KS_UVOFFH]);
		ks0127_write(sd, KS_UVOFFL, reg_defaults[KS_UVOFFL]);
		break;

	case KS_INPUT_SVIDEO_1:
	case KS_INPUT_SVIDEO_2:
	case KS_INPUT_SVIDEO_3:
		v4l2_dbg(1, debug, sd,
			"s_routing %d: S-Video\n", input);
		/* autodetect 50/60 Hz */
		ks0127_and_or(sd, KS_CMDA,   0xfc, 0x00);
		/* VSE=0 */
		ks0127_and_or(sd, KS_CMDA,   ~0x40, 0x00);
		/* set input line */
		ks0127_and_or(sd, KS_CMDB,   0xb0, input);
		/* non-freerunning mode */
		ks0127_and_or(sd, KS_CMDC,   0x70, 0x0a);
		/* analog input */
		ks0127_and_or(sd, KS_CMDD,   0x03, 0x00);
		/* enable chroma demodulation */
		ks0127_and_or(sd, KS_CTRACK, 0xcf, 0x00);
		ks0127_and_or(sd, KS_LUMA, 0x00,
			       reg_defaults[KS_LUMA]);
		/* disable luma comb */
		ks0127_and_or(sd, KS_VERTIA, 0x08,
			       (reg_defaults[KS_VERTIA]&0xf0)|0x01);
		ks0127_and_or(sd, KS_VERTIC, 0x0f,
			       reg_defaults[KS_VERTIC]&0xf0);

		ks0127_and_or(sd, KS_CHROMB, 0x0f,
			       reg_defaults[KS_CHROMB]&0xf0);

		ks0127_write(sd, KS_UGAIN, reg_defaults[KS_UGAIN]);
		ks0127_write(sd, KS_VGAIN, reg_defaults[KS_VGAIN]);
		ks0127_write(sd, KS_UVOFFH, reg_defaults[KS_UVOFFH]);
		ks0127_write(sd, KS_UVOFFL, reg_defaults[KS_UVOFFL]);
		break;

	case KS_INPUT_YUV656:
		v4l2_dbg(1, debug, sd, "s_routing 15: YUV656\n");
		if (ks->norm & V4L2_STD_525_60)
			/* force 60 Hz */
			ks0127_and_or(sd, KS_CMDA,   0xfc, 0x03);
		else
			/* force 50 Hz */
			ks0127_and_or(sd, KS_CMDA,   0xfc, 0x02);

		ks0127_and_or(sd, KS_CMDA,   0xff, 0x40); /* VSE=1 */
		/* set input line and VALIGN */
		ks0127_and_or(sd, KS_CMDB,   0xb0, (input | 0x40));
		/* freerunning mode, */
		/* TSTGEN = 1 TSTGFR=11 TSTGPH=0 TSTGPK=0  VMEM=1*/
		ks0127_and_or(sd, KS_CMDC,   0x70, 0x87);
		/* digital input, SYNDIR = 0 INPSL=01 CLKDIR=0 EAV=0 */
		ks0127_and_or(sd, KS_CMDD,   0x03, 0x08);
		/* disable chroma demodulation */
		ks0127_and_or(sd, KS_CTRACK, 0xcf, 0x30);
		/* HYPK =01 CTRAP = 0 HYBWR=0 PED=1 RGBH=1 UNIT=1 */
		ks0127_and_or(sd, KS_LUMA,   0x00, 0x71);
		ks0127_and_or(sd, KS_VERTIC, 0x0f,
			       reg_defaults[KS_VERTIC]&0xf0);

		/* scaler fullbw, luma comb off */
		ks0127_and_or(sd, KS_VERTIA, 0x08, 0x81);

		ks0127_and_or(sd, KS_CHROMB, 0x0f,
			       reg_defaults[KS_CHROMB]&0xf0);

		ks0127_and_or(sd, KS_CON, 0x00, 0x00);
		ks0127_and_or(sd, KS_BRT, 0x00, 32);	/* spec: 34 */
			/* spec: 229 (e5) */
		ks0127_and_or(sd, KS_SAT, 0x00, 0xe8);
		ks0127_and_or(sd, KS_HUE, 0x00, 0);

		ks0127_and_or(sd, KS_UGAIN, 0x00, 238);
		ks0127_and_or(sd, KS_VGAIN, 0x00, 0x00);

		/*UOFF:0x30, VOFF:0x30, TSTCGN=1 */
		ks0127_and_or(sd, KS_UVOFFH, 0x00, 0x4f);
		ks0127_and_or(sd, KS_UVOFFL, 0x00, 0x00);
		break;

	default:
		v4l2_dbg(1, debug, sd,
			"s_routing: Unknown input %d\n", input);
		break;
	}

	/* hack: CDMLPF sometimes spontaneously switches on; */
	/* force back off */
	ks0127_write(sd, KS_DEMOD, reg_defaults[KS_DEMOD]);
	return 0;
}