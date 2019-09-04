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
struct ivtv_dma_frame {int dummy; } ;
struct ivtv {int /*<<< orphan*/  serialize_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ivtv_yuv_next_free (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_yuv_setup_frame (struct ivtv*,struct ivtv_dma_frame*) ; 
 int ivtv_yuv_udma_frame (struct ivtv*,struct ivtv_dma_frame*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ivtv_yuv_prep_frame(struct ivtv *itv, struct ivtv_dma_frame *args)
{
	int res;

/*	IVTV_DEBUG_INFO("yuv_prep_frame\n"); */
	ivtv_yuv_next_free(itv);
	ivtv_yuv_setup_frame(itv, args);
	/* Wait for frame DMA. Note that serialize_lock is locked,
	   so to allow other processes to access the driver while
	   we are waiting unlock first and later lock again. */
	mutex_unlock(&itv->serialize_lock);
	res = ivtv_yuv_udma_frame(itv, args);
	mutex_lock(&itv->serialize_lock);
	return res;
}