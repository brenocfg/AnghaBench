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
struct pwc_device {int pixfmt; int vframes; scalar_t__ valternate; int width; int height; int frame_size; int release; int vbandlength; int /*<<< orphan*/  vendpoint; } ;
struct Nala_table_entry {scalar_t__ alternate; scalar_t__ compressed; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int EINVAL ; 
 struct Nala_table_entry** Nala_table ; 
 int PSZ_CIF ; 
 int PSZ_QCIF ; 
 int V4L2_PIX_FMT_YUV420 ; 
 int /*<<< orphan*/  pwc_dec1_init (struct pwc_device*,int /*<<< orphan*/ ) ; 
 void*** pwc_image_sizes ; 
 int send_video_command (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_video_mode_Nala(struct pwc_device *pdev, int size, int pixfmt,
			       int frames, int *compression, int send_to_cam)
{
	int fps, ret = 0;
	struct Nala_table_entry *pEntry;
	int frames2frames[31] =
	{ /* closest match of framerate */
	   0,  0,  0,  0,  4,  /*  0-4  */
	   5,  5,  7,  7, 10,  /*  5-9  */
	  10, 10, 12, 12, 15,  /* 10-14 */
	  15, 15, 15, 20, 20,  /* 15-19 */
	  20, 20, 20, 24, 24,  /* 20-24 */
	  24, 24, 24, 24, 24,  /* 25-29 */
	  24                   /* 30    */
	};
	int frames2table[31] =
	{ 0, 0, 0, 0, 0, /*  0-4  */
	  1, 1, 1, 2, 2, /*  5-9  */
	  3, 3, 4, 4, 4, /* 10-14 */
	  5, 5, 5, 5, 5, /* 15-19 */
	  6, 6, 6, 6, 7, /* 20-24 */
	  7, 7, 7, 7, 7, /* 25-29 */
	  7              /* 30    */
	};

	if (size < 0 || size > PSZ_CIF)
		return -EINVAL;
	if (frames < 4)
		frames = 4;
	else if (size > PSZ_QCIF && frames > 15)
		frames = 15;
	else if (frames > 25)
		frames = 25;
	frames = frames2frames[frames];
	fps = frames2table[frames];
	pEntry = &Nala_table[size][fps];
	if (pEntry->alternate == 0)
		return -EINVAL;

	if (send_to_cam)
		ret = send_video_command(pdev, pdev->vendpoint,
					 pEntry->mode, 3);
	if (ret < 0)
		return ret;

	if (pEntry->compressed && pixfmt == V4L2_PIX_FMT_YUV420)
		pwc_dec1_init(pdev, pEntry->mode);

	/* Set various parameters */
	pdev->pixfmt = pixfmt;
	pdev->vframes = frames;
	pdev->valternate = pEntry->alternate;
	pdev->width  = pwc_image_sizes[size][0];
	pdev->height = pwc_image_sizes[size][1];
	pdev->frame_size = (pdev->width * pdev->height * 3) / 2;
	if (pEntry->compressed) {
		if (pdev->release < 5) { /* 4 fold compression */
			pdev->vbandlength = 528;
			pdev->frame_size /= 4;
		}
		else {
			pdev->vbandlength = 704;
			pdev->frame_size /= 3;
		}
	}
	else
		pdev->vbandlength = 0;

	/* Let pwc-if.c:isoc_init know we don't support higher compression */
	*compression = 3;

	return 0;
}