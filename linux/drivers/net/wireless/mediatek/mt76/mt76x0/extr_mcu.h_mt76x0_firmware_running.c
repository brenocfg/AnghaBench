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
struct mt76x02_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_MCU_COM_REG0 ; 
 int mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int mt76x0_firmware_running(struct mt76x02_dev *dev)
{
	return mt76_rr(dev, MT_MCU_COM_REG0) == 1;
}