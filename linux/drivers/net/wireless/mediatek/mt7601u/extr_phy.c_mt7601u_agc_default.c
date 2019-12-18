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
typedef  int u8 ;
struct mt7601u_dev {TYPE_1__* ee; } ;
struct TYPE_2__ {int lna_gain; } ;

/* Variables and functions */

__attribute__((used)) static u8 mt7601u_agc_default(struct mt7601u_dev *dev)
{
	return (dev->ee->lna_gain - 8) * 2 + 0x34;
}