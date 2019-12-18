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
struct mt76_txwi_cache {int dummy; } ;
struct mt76_dev {int dummy; } ;
struct mt7615_txp {int dummy; } ;

/* Variables and functions */
 int MT_TXD_SIZE ; 
 int /*<<< orphan*/ * mt76_get_txwi_ptr (struct mt76_dev*,struct mt76_txwi_cache*) ; 

__attribute__((used)) static inline struct mt7615_txp *
mt7615_txwi_to_txp(struct mt76_dev *dev, struct mt76_txwi_cache *t)
{
	u8 *txwi;

	if (!t)
		return NULL;

	txwi = mt76_get_txwi_ptr(dev, t);

	return (struct mt7615_txp *)(txwi + MT_TXD_SIZE);
}