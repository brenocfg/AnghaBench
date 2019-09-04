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
struct mic_device {int /*<<< orphan*/  dp; int /*<<< orphan*/  dp_dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIC_DP_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mic_unmap_single (struct mic_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mic_dp_uninit(struct mic_device *mdev)
{
	mic_unmap_single(mdev, mdev->dp_dma_addr, MIC_DP_SIZE);
	kfree(mdev->dp);
}