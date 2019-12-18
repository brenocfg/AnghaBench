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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_MAC_FULL ; 
 int HCLGE_MAC_SPEED_100M ; 
 int HCLGE_MAC_SPEED_10M ; 

__attribute__((used)) static u8 hclge_check_speed_dup(u8 duplex, int speed)
{
	if (!(speed == HCLGE_MAC_SPEED_10M || speed == HCLGE_MAC_SPEED_100M))
		duplex = HCLGE_MAC_FULL;

	return duplex;
}