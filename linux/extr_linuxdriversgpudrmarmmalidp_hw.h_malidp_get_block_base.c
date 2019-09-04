#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct malidp_hw_device {TYPE_2__* hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  dc_base; int /*<<< orphan*/  se_base; } ;
struct TYPE_4__ {TYPE_1__ map; } ;

/* Variables and functions */
#define  MALIDP_DC_BLOCK 129 
#define  MALIDP_SE_BLOCK 128 

__attribute__((used)) static inline u32 malidp_get_block_base(struct malidp_hw_device *hwdev,
					u8 block)
{
	switch (block) {
	case MALIDP_SE_BLOCK:
		return hwdev->hw->map.se_base;
	case MALIDP_DC_BLOCK:
		return hwdev->hw->map.dc_base;
	}

	return 0;
}