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
typedef  int /*<<< orphan*/  u8 ;
struct mt76_txwi_cache {int dummy; } ;
struct mt76_dev {TYPE_1__* drv; } ;
struct TYPE_2__ {int txwi_size; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 *
mt76_get_txwi_ptr(struct mt76_dev *dev, struct mt76_txwi_cache *t)
{
	return (u8 *)t - dev->drv->txwi_size;
}