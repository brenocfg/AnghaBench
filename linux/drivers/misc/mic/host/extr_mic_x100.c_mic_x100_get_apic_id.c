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
typedef  int /*<<< orphan*/  u32 ;
struct mic_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_spad ) (struct mic_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MIC_X100_DOWNLOAD_INFO ; 
 int /*<<< orphan*/  MIC_X100_SPAD2_APIC_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mic_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 mic_x100_get_apic_id(struct mic_device *mdev)
{
	u32 scratch2 = 0;

	scratch2 = mdev->ops->read_spad(mdev, MIC_X100_DOWNLOAD_INFO);
	return MIC_X100_SPAD2_APIC_ID(scratch2);
}