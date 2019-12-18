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
typedef  int /*<<< orphan*/  u32 ;
struct mt7601u_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt7601u_bbp_rmc (struct mt7601u_dev*,int,int,int) ; 

u32 mt7601u_bbp_set_ctrlch(struct mt7601u_dev *dev, bool below)
{
	return mt7601u_bbp_rmc(dev, 3, 0x20, below ? 0x20 : 0);
}