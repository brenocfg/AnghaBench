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
struct output_desc {int h_vis; int h_f_porch; int h_sync; int h_b_porch; unsigned long long chromasc; int burst; int v_total; } ;
struct TYPE_2__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; int member_8; int member_9; int member_10; int member_11; int member_12; int member_13; int member_14; int member_15; int member_16; int member_17; int member_18; int member_19; int member_20; int member_21; int member_22; int member_23; int member_24; int member_25; int member_26; int member_27; int member_28; int member_29; int member_30; int member_31; int member_32; int member_33; int member_34; int member_35; int member_36; int member_37; int member_38; int member_39; int member_40; int member_41; int member_42; int member_43; int member_44; int member_45; int member_46; int member_47; int member_48; int member_49; int member_50; int member_51; int member_52; int member_53; int member_54; int member_55; int member_56; int member_57; int member_58; int member_59; int member_60; int member_61; int member_62; int member_63; } ;
struct mavenregs {TYPE_1__ member_0; } ;

/* Variables and functions */
 int MATROXFB_OUTPUT_MODE_PAL ; 

__attribute__((used)) static void cve2_init_TVdata(int norm, struct mavenregs* data, const struct output_desc** outd) {
	static const struct output_desc paloutd = {
		.h_vis	   = 52148148,	// ps
		.h_f_porch =  1407407,	// ps
		.h_sync    =  4666667,	// ps
		.h_b_porch =  5777778,	// ps
		.chromasc  = 19042247534182ULL,	// 4433618.750 Hz
		.burst     =  2518518,	// ps
		.v_total   =      625,
	};
	static const struct output_desc ntscoutd = {
		.h_vis     = 52888889,	// ps
		.h_f_porch =  1333333,	// ps
		.h_sync    =  4666667,	// ps
		.h_b_porch =  4666667,	// ps
		.chromasc  = 15374030659475ULL,	// 3579545.454 Hz
		.burst     =  2418418,	// ps
		.v_total   =      525,	// lines
	};

	static const struct mavenregs palregs = { {
		0x2A, 0x09, 0x8A, 0xCB,	/* 00: chroma subcarrier */
		0x00,
		0x00,	/* test */
		0xF9,	/* modified by code (F9 written...) */
		0x00,	/* ? not written */
		0x7E,	/* 08 */
		0x44,	/* 09 */
		0x9C,	/* 0A */
		0x2E,	/* 0B */
		0x21,	/* 0C */
		0x00,	/* ? not written */
//		0x3F, 0x03, /* 0E-0F */
		0x3C, 0x03,
		0x3C, 0x03, /* 10-11 */
		0x1A,	/* 12 */
		0x2A,	/* 13 */
		0x1C, 0x3D, 0x14, /* 14-16 */
		0x9C, 0x01, /* 17-18 */
		0x00,	/* 19 */
		0xFE,	/* 1A */
		0x7E,	/* 1B */
		0x60,	/* 1C */
		0x05,	/* 1D */
//		0x89, 0x03, /* 1E-1F */
		0xAD, 0x03,
//		0x72,	/* 20 */
		0xA5,
		0x07,	/* 21 */
//		0x72,	/* 22 */
		0xA5,
		0x00,	/* 23 */
		0x00,	/* 24 */
		0x00,	/* 25 */
		0x08,	/* 26 */
		0x04,	/* 27 */
		0x00,	/* 28 */
		0x1A,	/* 29 */
		0x55, 0x01, /* 2A-2B */
		0x26,	/* 2C */
		0x07, 0x7E, /* 2D-2E */
		0x02, 0x54, /* 2F-30 */
		0xB0, 0x00, /* 31-32 */
		0x14,	/* 33 */
		0x49,	/* 34 */
		0x00,	/* 35 written multiple times */
		0x00,	/* 36 not written */
		0xA3,	/* 37 */
		0xC8,	/* 38 */
		0x22,	/* 39 */
		0x02,	/* 3A */
		0x22,	/* 3B */
		0x3F, 0x03, /* 3C-3D */
		0x00,	/* 3E written multiple times */
		0x00,	/* 3F not written */
	} };
	static const struct mavenregs ntscregs = { {
		0x21, 0xF0, 0x7C, 0x1F,	/* 00: chroma subcarrier */
		0x00,
		0x00,	/* test */
		0xF9,	/* modified by code (F9 written...) */
		0x00,	/* ? not written */
		0x7E,	/* 08 */
		0x43,	/* 09 */
		0x7E,	/* 0A */
		0x3D,	/* 0B */
		0x00,	/* 0C */
		0x00,	/* ? not written */
		0x41, 0x00, /* 0E-0F */
		0x3C, 0x00, /* 10-11 */
		0x17,	/* 12 */
		0x21,	/* 13 */
		0x1B, 0x1B, 0x24, /* 14-16 */
		0x83, 0x01, /* 17-18 */
		0x00,	/* 19 */
		0x0F,	/* 1A */
		0x0F,	/* 1B */
		0x60,	/* 1C */
		0x05,	/* 1D */
		//0x89, 0x02, /* 1E-1F */
		0xC0, 0x02, /* 1E-1F */
		//0x5F,	/* 20 */
		0x9C,	/* 20 */
		0x04,	/* 21 */
		//0x5F,	/* 22 */
		0x9C,	/* 22 */
		0x01,	/* 23 */
		0x02,	/* 24 */
		0x00,	/* 25 */
		0x0A,	/* 26 */
		0x05,	/* 27 */
		0x00,	/* 28 */
		0x10,	/* 29 */
		0xFF, 0x03, /* 2A-2B */
		0x24,	/* 2C */
		0x0F, 0x78, /* 2D-2E */
		0x00, 0x00, /* 2F-30 */
		0xB2, 0x04, /* 31-32 */
		0x14,	/* 33 */
		0x02,	/* 34 */
		0x00,	/* 35 written multiple times */
		0x00,	/* 36 not written */
		0xA3,	/* 37 */
		0xC8,	/* 38 */
		0x15,	/* 39 */
		0x05,	/* 3A */
		0x3B,	/* 3B */
		0x3C, 0x00, /* 3C-3D */
		0x00,	/* 3E written multiple times */
		0x00,	/* never written */
	} };

	if (norm == MATROXFB_OUTPUT_MODE_PAL) {
		*data = palregs;
		*outd = &paloutd;
	} else {
  		*data = ntscregs;
		*outd = &ntscoutd;
	}
 	return;
}