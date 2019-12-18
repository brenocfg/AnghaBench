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
typedef  int u16 ;
struct go7007 {int sensor_framerate; int fps_scale; int height; int width; TYPE_1__* board_info; int /*<<< orphan*/  modet_enable; scalar_t__ interlace_coding; int /*<<< orphan*/  ipb; int /*<<< orphan*/  gop_header_enable; int /*<<< orphan*/  dvd_mode; int /*<<< orphan*/  repeat_seqhead; int /*<<< orphan*/  format; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int sensor_flags; int hpi_buffer_cap; } ;

/* Variables and functions */
 int GO7007_SENSOR_TV ; 
 int GO7007_SENSOR_VBI ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_H263 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_MPEG1 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_MPEG2 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_MPEG4 ; 
 int copy_packages (int /*<<< orphan*/ *,int*,int,int) ; 

__attribute__((used)) static int config_package(struct go7007 *go, __le16 *code, int space)
{
	int fps = go->sensor_framerate / go->fps_scale / 1000;
	int rows = go->interlace_coding ? go->height / 32 : go->height / 16;
	int brc_window_size = fps;
	int q_min = 2, q_max = 31;
	int THACCoeffSet0 = 0;
	u16 pack[] = {
		0x200e,		0x0000,
		0xc002,		0x14b4,
		0xc003,		0x28b4,
		0xc004,		0x3c5a,
		0xdc05,		0x2a77,
		0xc6c3,		go->format == V4L2_PIX_FMT_MPEG4 ? 0 :
				(go->format == V4L2_PIX_FMT_H263 ? 0 : 1),
		0xc680,		go->format == V4L2_PIX_FMT_MPEG4 ? 0xf1 :
				(go->format == V4L2_PIX_FMT_H263 ? 0x61 :
									0xd3),
		0xc780,		0x0140,
		0xe009,		0x0001,
		0xc60f,		0x0008,
		0xd4ff,		0x0002,
		0xe403,		2340,
		0xe406,		75,
		0xd411,		0x0001,
		0xd410,		0xa1d6,
		0x0001,		0x2801,

		0x200d,		0x0000,
		0xe402,		0x018b,
		0xe401,		0x8b01,
		0xd472,		(go->board_info->sensor_flags &
							GO7007_SENSOR_TV) &&
						(!go->interlace_coding) ?
					0x01b0 : 0x0170,
		0xd475,		(go->board_info->sensor_flags &
							GO7007_SENSOR_TV) &&
						(!go->interlace_coding) ?
					0x0008 : 0x0009,
		0xc404,		go->interlace_coding ? 0x44 :
				(go->format == V4L2_PIX_FMT_MPEG4 ? 0x11 :
				(go->format == V4L2_PIX_FMT_MPEG1 ? 0x02 :
				(go->format == V4L2_PIX_FMT_MPEG2 ? 0x04 :
				(go->format == V4L2_PIX_FMT_H263  ? 0x08 :
								     0x20)))),
		0xbf0a,		(go->format == V4L2_PIX_FMT_MPEG4 ? 8 :
				(go->format == V4L2_PIX_FMT_MPEG1 ? 1 :
				(go->format == V4L2_PIX_FMT_MPEG2 ? 2 :
				(go->format == V4L2_PIX_FMT_H263 ? 4 : 16)))) |
				((go->repeat_seqhead ? 1 : 0) << 6) |
				((go->dvd_mode ? 1 : 0) << 9) |
				((go->gop_header_enable ? 1 : 0) << 10),
		0xbf0b,		0,
		0xdd5a,		go->ipb ? 0x14 : 0x0a,
		0xbf0c,		0,
		0xbf0d,		0,
		0xc683,		THACCoeffSet0,
		0xc40a,		(go->width << 4) | rows,
		0xe01a,		go->board_info->hpi_buffer_cap,
		0,		0,
		0,		0,

		0x2008,		0,
		0xe402,		0x88,
		0xe401,		0x8f01,
		0xbf6a,		0,
		0xbf6b,		0,
		0xbf6c,		0,
		0xbf6d,		0,
		0xbf6e,		0,
		0xbf6f,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,

		0x200e,		0,
		0xbf66,		brc_window_size,
		0xbf67,		0,
		0xbf68,		q_min,
		0xbf69,		q_max,
		0xbfe0,		0,
		0xbfe1,		0,
		0xbfe2,		0,
		0xbfe3,		go->ipb ? 3 : 1,
		0xc031,		go->board_info->sensor_flags &
					GO7007_SENSOR_VBI ? 1 : 0,
		0xc01c,		0x1f,
		0xdd8c,		0x15,
		0xdd94,		0x15,
		0xdd88,		go->ipb ? 0x1401 : 0x0a01,
		0xdd90,		go->ipb ? 0x1401 : 0x0a01,
		0,		0,

		0x200e,		0,
		0xbfe4,		0,
		0xbfe5,		0,
		0xbfe6,		0,
		0xbfe7,		fps << 8,
		0xbfe8,		0x3a00,
		0xbfe9,		0,
		0xbfea,		0,
		0xbfeb,		0,
		0xbfec,		(go->interlace_coding ? 1 << 15 : 0) |
					(go->modet_enable ? 0xa : 0) |
					(go->board_info->sensor_flags &
						GO7007_SENSOR_VBI ? 1 : 0),
		0xbfed,		0,
		0xbfee,		0,
		0xbfef,		0,
		0xbff0,		go->board_info->sensor_flags &
					GO7007_SENSOR_TV ? 0xf060 : 0xb060,
		0xbff1,		0,
		0,		0,
	};

	return copy_packages(code, pack, 5, space);
}