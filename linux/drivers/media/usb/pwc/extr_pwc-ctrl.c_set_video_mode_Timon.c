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
struct pwc_device {int pixfmt; int vframes; scalar_t__ valternate; int width; int height; int vbandlength; int frame_size; int /*<<< orphan*/  vendpoint; } ;
struct Timon_table_entry {scalar_t__ alternate; int bandlength; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int PSZ_MAX ; 
 int PSZ_VGA ; 
 struct Timon_table_entry*** Timon_table ; 
 int V4L2_PIX_FMT_YUV420 ; 
 int /*<<< orphan*/  pwc_dec23_init (struct pwc_device*,int /*<<< orphan*/ ) ; 
 void*** pwc_image_sizes ; 
 int send_video_command (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_video_mode_Timon(struct pwc_device *pdev, int size, int pixfmt,
				int frames, int *compression, int send_to_cam)
{
	const struct Timon_table_entry *pChoose;
	int fps, ret = 0;

	if (size >= PSZ_MAX || *compression < 0 || *compression > 3)
		return -EINVAL;
	if (frames < 5)
		frames = 5;
	else if (size == PSZ_VGA && frames > 15)
		frames = 15;
	else if (frames > 30)
		frames = 30;
	fps = (frames / 5) - 1;

	/* Find a supported framerate with progressively higher compression */
	do {
		pChoose = &Timon_table[size][fps][*compression];
		if (pChoose->alternate != 0)
			break;
		(*compression)++;
	} while (*compression <= 3);

	if (pChoose->alternate == 0)
		return -ENOENT; /* Not supported. */

	if (send_to_cam)
		ret = send_video_command(pdev, pdev->vendpoint,
					 pChoose->mode, 13);
	if (ret < 0)
		return ret;

	if (pChoose->bandlength > 0 && pixfmt == V4L2_PIX_FMT_YUV420)
		pwc_dec23_init(pdev, pChoose->mode);

	/* Set various parameters */
	pdev->pixfmt = pixfmt;
	pdev->vframes = (fps + 1) * 5;
	pdev->valternate = pChoose->alternate;
	pdev->width  = pwc_image_sizes[size][0];
	pdev->height = pwc_image_sizes[size][1];
	pdev->vbandlength = pChoose->bandlength;
	if (pChoose->bandlength > 0)
		pdev->frame_size = (pChoose->bandlength * pdev->height) / 4;
	else
		pdev->frame_size = (pdev->width * pdev->height * 12) / 8;
	return 0;
}