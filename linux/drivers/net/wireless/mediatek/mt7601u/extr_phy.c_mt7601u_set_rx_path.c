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
typedef  int u8 ;
struct mt7601u_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt7601u_bbp_rmw (struct mt7601u_dev*,int,int,int) ; 

void mt7601u_set_rx_path(struct mt7601u_dev *dev, u8 path)
{
	mt7601u_bbp_rmw(dev, 3, 0x18, path << 3);
}