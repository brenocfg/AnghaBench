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
struct mic_device {int num_dma_ch; int /*<<< orphan*/ ** dma_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mic_free_dma_chans(struct mic_device *mdev)
{
	int i = 0;

	for (i = 0; i < mdev->num_dma_ch; i++) {
		dma_release_channel(mdev->dma_ch[i]);
		mdev->dma_ch[i] = NULL;
	}
	mdev->num_dma_ch = 0;
}