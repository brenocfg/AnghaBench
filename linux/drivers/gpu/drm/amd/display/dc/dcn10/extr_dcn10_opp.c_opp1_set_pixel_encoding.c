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
struct dcn10_opp {int dummy; } ;
struct clamping_and_pixel_encoding_params {int pixel_encoding; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMT_CONTROL ; 
 int /*<<< orphan*/  FMT_PIXEL_ENCODING ; 
#define  PIXEL_ENCODING_RGB 131 
#define  PIXEL_ENCODING_YCBCR420 130 
#define  PIXEL_ENCODING_YCBCR422 129 
#define  PIXEL_ENCODING_YCBCR444 128 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void opp1_set_pixel_encoding(
	struct dcn10_opp *oppn10,
	const struct clamping_and_pixel_encoding_params *params)
{
	switch (params->pixel_encoding)	{

	case PIXEL_ENCODING_RGB:
	case PIXEL_ENCODING_YCBCR444:
		REG_UPDATE(FMT_CONTROL, FMT_PIXEL_ENCODING, 0);
		break;
	case PIXEL_ENCODING_YCBCR422:
		REG_UPDATE(FMT_CONTROL, FMT_PIXEL_ENCODING, 1);
		break;
	case PIXEL_ENCODING_YCBCR420:
		REG_UPDATE(FMT_CONTROL, FMT_PIXEL_ENCODING, 2);
		break;
	default:
		break;
	}
}