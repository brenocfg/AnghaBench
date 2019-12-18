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
typedef  int /*<<< orphan*/  u32 ;
struct mt7603_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_WPDMA_DEBUG ; 
 int /*<<< orphan*/  MT_WPDMA_DEBUG_IDX ; 
 int MT_WPDMA_DEBUG_SEL ; 
 int /*<<< orphan*/  MT_WPDMA_DEBUG_VALUE ; 
 int /*<<< orphan*/  mt76_rr (struct mt7603_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 mt7603_dma_debug(struct mt7603_dev *dev, u8 index)
{
	u32 val;

	mt76_wr(dev, MT_WPDMA_DEBUG,
		FIELD_PREP(MT_WPDMA_DEBUG_IDX, index) |
		MT_WPDMA_DEBUG_SEL);

	val = mt76_rr(dev, MT_WPDMA_DEBUG);
	return FIELD_GET(MT_WPDMA_DEBUG_VALUE, val);
}