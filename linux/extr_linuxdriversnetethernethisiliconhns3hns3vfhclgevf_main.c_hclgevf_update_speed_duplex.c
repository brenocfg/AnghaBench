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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct hclgevf_dev {TYPE_2__ hw; } ;

/* Variables and functions */

void hclgevf_update_speed_duplex(struct hclgevf_dev *hdev, u32 speed,
				 u8 duplex)
{
	hdev->hw.mac.speed = speed;
	hdev->hw.mac.duplex = duplex;
}