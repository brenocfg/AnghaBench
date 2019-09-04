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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
#define  MEDIA_BUS_FMT_SBGGR8_1X8 131 
#define  MEDIA_BUS_FMT_SGBRG8_1X8 130 
#define  MEDIA_BUS_FMT_SGRBG8_1X8 129 
#define  MEDIA_BUS_FMT_SRGGB8_1X8 128 
 int /*<<< orphan*/  XTPG_BAYER_PHASE_BGGR ; 
 int /*<<< orphan*/  XTPG_BAYER_PHASE_GBRG ; 
 int /*<<< orphan*/  XTPG_BAYER_PHASE_GRBG ; 
 int /*<<< orphan*/  XTPG_BAYER_PHASE_OFF ; 
 int /*<<< orphan*/  XTPG_BAYER_PHASE_RGGB ; 

__attribute__((used)) static u32 xtpg_get_bayer_phase(unsigned int code)
{
	switch (code) {
	case MEDIA_BUS_FMT_SRGGB8_1X8:
		return XTPG_BAYER_PHASE_RGGB;
	case MEDIA_BUS_FMT_SGRBG8_1X8:
		return XTPG_BAYER_PHASE_GRBG;
	case MEDIA_BUS_FMT_SGBRG8_1X8:
		return XTPG_BAYER_PHASE_GBRG;
	case MEDIA_BUS_FMT_SBGGR8_1X8:
		return XTPG_BAYER_PHASE_BGGR;
	default:
		return XTPG_BAYER_PHASE_OFF;
	}
}