#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int width; int height; } ;
struct TYPE_4__ {int video_size; } ;
struct TYPE_6__ {TYPE_2__ roi; TYPE_1__ vp_params; } ;
struct camera_data {int width; int height; TYPE_3__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int EINVAL ; 
 void* STV_IMAGE_CIF_COLS ; 
 void* STV_IMAGE_CIF_ROWS ; 
 void* STV_IMAGE_QCIF_COLS ; 
 void* STV_IMAGE_QCIF_ROWS ; 
 void* STV_IMAGE_QVGA_COLS ; 
 void* STV_IMAGE_QVGA_ROWS ; 
 void* STV_IMAGE_VGA_COLS ; 
 void* STV_IMAGE_VGA_ROWS ; 
#define  VIDEOSIZE_192_144 135 
#define  VIDEOSIZE_224_168 134 
#define  VIDEOSIZE_256_192 133 
#define  VIDEOSIZE_288_216 132 
#define  VIDEOSIZE_CIF 131 
#define  VIDEOSIZE_QCIF 130 
#define  VIDEOSIZE_QVGA 129 
#define  VIDEOSIZE_VGA 128 

__attribute__((used)) static int set_vw_size(struct camera_data *cam, int size)
{
	int retval = 0;

	cam->params.vp_params.video_size = size;

	switch (size) {
	case VIDEOSIZE_VGA:
		DBG("Setting size to VGA\n");
		cam->params.roi.width = STV_IMAGE_VGA_COLS;
		cam->params.roi.height = STV_IMAGE_VGA_ROWS;
		cam->width = STV_IMAGE_VGA_COLS;
		cam->height = STV_IMAGE_VGA_ROWS;
		break;
	case VIDEOSIZE_CIF:
		DBG("Setting size to CIF\n");
		cam->params.roi.width = STV_IMAGE_CIF_COLS;
		cam->params.roi.height = STV_IMAGE_CIF_ROWS;
		cam->width = STV_IMAGE_CIF_COLS;
		cam->height = STV_IMAGE_CIF_ROWS;
		break;
	case VIDEOSIZE_QVGA:
		DBG("Setting size to QVGA\n");
		cam->params.roi.width = STV_IMAGE_QVGA_COLS;
		cam->params.roi.height = STV_IMAGE_QVGA_ROWS;
		cam->width = STV_IMAGE_QVGA_COLS;
		cam->height = STV_IMAGE_QVGA_ROWS;
		break;
	case VIDEOSIZE_288_216:
		cam->params.roi.width = 288;
		cam->params.roi.height = 216;
		cam->width = 288;
		cam->height = 216;
		break;
	case VIDEOSIZE_256_192:
		cam->width = 256;
		cam->height = 192;
		cam->params.roi.width = 256;
		cam->params.roi.height = 192;
		break;
	case VIDEOSIZE_224_168:
		cam->width = 224;
		cam->height = 168;
		cam->params.roi.width = 224;
		cam->params.roi.height = 168;
		break;
	case VIDEOSIZE_192_144:
		cam->width = 192;
		cam->height = 144;
		cam->params.roi.width = 192;
		cam->params.roi.height = 144;
		break;
	case VIDEOSIZE_QCIF:
		DBG("Setting size to QCIF\n");
		cam->params.roi.width = STV_IMAGE_QCIF_COLS;
		cam->params.roi.height = STV_IMAGE_QCIF_ROWS;
		cam->width = STV_IMAGE_QCIF_COLS;
		cam->height = STV_IMAGE_QCIF_ROWS;
		break;
	default:
		retval = -EINVAL;
	}
	return retval;
}