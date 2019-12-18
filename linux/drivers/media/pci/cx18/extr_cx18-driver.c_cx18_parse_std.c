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
typedef  int v4l2_std_id ;
struct cx18 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_WARN (char*) ; 
 int V4L2_STD_NTSC_M ; 
 int V4L2_STD_NTSC_M_JP ; 
 int V4L2_STD_NTSC_M_KR ; 
 int V4L2_STD_PAL_60 ; 
 int V4L2_STD_PAL_BG ; 
 int V4L2_STD_PAL_DK ; 
 int V4L2_STD_PAL_H ; 
 int V4L2_STD_PAL_I ; 
 int V4L2_STD_PAL_M ; 
 int V4L2_STD_PAL_N ; 
 int V4L2_STD_PAL_Nc ; 
 int V4L2_STD_SECAM_B ; 
 int V4L2_STD_SECAM_DK ; 
 int V4L2_STD_SECAM_G ; 
 int V4L2_STD_SECAM_H ; 
 int V4L2_STD_SECAM_L ; 
 int V4L2_STD_SECAM_LC ; 
 int* ntsc ; 
 int* pal ; 
 int* secam ; 

__attribute__((used)) static v4l2_std_id cx18_parse_std(struct cx18 *cx)
{
	switch (pal[0]) {
	case '6':
		return V4L2_STD_PAL_60;
	case 'b':
	case 'B':
	case 'g':
	case 'G':
		return V4L2_STD_PAL_BG;
	case 'h':
	case 'H':
		return V4L2_STD_PAL_H;
	case 'n':
	case 'N':
		if (pal[1] == 'c' || pal[1] == 'C')
			return V4L2_STD_PAL_Nc;
		return V4L2_STD_PAL_N;
	case 'i':
	case 'I':
		return V4L2_STD_PAL_I;
	case 'd':
	case 'D':
	case 'k':
	case 'K':
		return V4L2_STD_PAL_DK;
	case 'M':
	case 'm':
		return V4L2_STD_PAL_M;
	case '-':
		break;
	default:
		CX18_WARN("pal= argument not recognised\n");
		return 0;
	}

	switch (secam[0]) {
	case 'b':
	case 'B':
	case 'g':
	case 'G':
	case 'h':
	case 'H':
		return V4L2_STD_SECAM_B | V4L2_STD_SECAM_G | V4L2_STD_SECAM_H;
	case 'd':
	case 'D':
	case 'k':
	case 'K':
		return V4L2_STD_SECAM_DK;
	case 'l':
	case 'L':
		if (secam[1] == 'C' || secam[1] == 'c')
			return V4L2_STD_SECAM_LC;
		return V4L2_STD_SECAM_L;
	case '-':
		break;
	default:
		CX18_WARN("secam= argument not recognised\n");
		return 0;
	}

	switch (ntsc[0]) {
	case 'm':
	case 'M':
		return V4L2_STD_NTSC_M;
	case 'j':
	case 'J':
		return V4L2_STD_NTSC_M_JP;
	case 'k':
	case 'K':
		return V4L2_STD_NTSC_M_KR;
	case '-':
		break;
	default:
		CX18_WARN("ntsc= argument not recognised\n");
		return 0;
	}

	/* no match found */
	return 0;
}