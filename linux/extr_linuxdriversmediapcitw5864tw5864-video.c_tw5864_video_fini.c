#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tw5864_dev {TYPE_4__* h264_buf; TYPE_2__* pci; int /*<<< orphan*/ * inputs; int /*<<< orphan*/  tasklet; } ;
struct TYPE_7__ {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_3__ mv; TYPE_1__ vlc; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int H264_BUF_CNT ; 
 int /*<<< orphan*/  H264_MV_BUF_SIZE ; 
 int /*<<< orphan*/  H264_VLC_BUF_SIZE ; 
 int TW5864_INPUTS ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tw5864_video_input_fini (int /*<<< orphan*/ *) ; 

void tw5864_video_fini(struct tw5864_dev *dev)
{
	int i;

	tasklet_kill(&dev->tasklet);

	for (i = 0; i < TW5864_INPUTS; i++)
		tw5864_video_input_fini(&dev->inputs[i]);

	for (i = 0; i < H264_BUF_CNT; i++) {
		dma_free_coherent(&dev->pci->dev, H264_VLC_BUF_SIZE,
				  dev->h264_buf[i].vlc.addr,
				  dev->h264_buf[i].vlc.dma_addr);
		dma_free_coherent(&dev->pci->dev, H264_MV_BUF_SIZE,
				  dev->h264_buf[i].mv.addr,
				  dev->h264_buf[i].mv.dma_addr);
	}
}