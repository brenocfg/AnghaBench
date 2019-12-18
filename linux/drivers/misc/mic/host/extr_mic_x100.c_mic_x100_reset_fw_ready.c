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
struct mic_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_spad ) (struct mic_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MIC_X100_DOWNLOAD_INFO ; 
 int /*<<< orphan*/  stub1 (struct mic_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mic_x100_reset_fw_ready(struct mic_device *mdev)
{
	mdev->ops->write_spad(mdev, MIC_X100_DOWNLOAD_INFO, 0);
}