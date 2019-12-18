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
typedef  int u32 ;
struct malidp_hw_device {TYPE_2__* hw; } ;
struct TYPE_3__ {scalar_t__ dc_base; } ;
struct TYPE_4__ {TYPE_1__ map; } ;

/* Variables and functions */
 int MALIDP500_DC_CONFIG_REQ ; 
 scalar_t__ MALIDP_REG_STATUS ; 
 int malidp_hw_read (struct malidp_hw_device*,scalar_t__) ; 

__attribute__((used)) static bool malidp500_in_config_mode(struct malidp_hw_device *hwdev)
{
	u32 status;

	status = malidp_hw_read(hwdev, hwdev->hw->map.dc_base + MALIDP_REG_STATUS);
	if ((status & MALIDP500_DC_CONFIG_REQ) == MALIDP500_DC_CONFIG_REQ)
		return true;

	return false;
}