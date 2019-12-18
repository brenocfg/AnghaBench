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
struct mt76x02_dev {int /*<<< orphan*/  mt76; } ;

/* Variables and functions */
 int mt76_chip (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool is_mt7630(struct mt76x02_dev *dev)
{
	return mt76_chip(&dev->mt76) == 0x7630;
}