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
typedef  scalar_t__ u8 ;
struct hclge_mac {int speed; scalar_t__ duplex; } ;
struct TYPE_2__ {struct hclge_mac mac; } ;
struct hclge_dev {TYPE_1__ hw; } ;

/* Variables and functions */
 scalar_t__ HCLGE_MAC_FULL ; 
 int HCLGE_MAC_SPEED_100M ; 
 int HCLGE_MAC_SPEED_10M ; 

__attribute__((used)) static void hclge_check_speed_dup(struct hclge_dev *hdev, int duplex, int speed)
{
	struct hclge_mac *mac = &hdev->hw.mac;

	if ((speed == HCLGE_MAC_SPEED_10M) || (speed == HCLGE_MAC_SPEED_100M))
		mac->duplex = (u8)duplex;
	else
		mac->duplex = HCLGE_MAC_FULL;

	mac->speed = speed;
}