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
struct tssi_data {int slope; int* offset; } ;
struct mt7601u_dev {TYPE_1__* ee; } ;
typedef  int s16 ;
struct TYPE_2__ {struct tssi_data tssi_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_TX_ALC_CFG_1 ; 
 int MT_TX_ALC_CFG_1_TEMP_COMP ; 
 int int_to_s6 (int) ; 
 int /*<<< orphan*/  mt76_rmw (struct mt7601u_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
mt7601u_set_initial_tssi(struct mt7601u_dev *dev, s16 tssi_db, s16 tssi_hvga_db)
{
	struct tssi_data *d = &dev->ee->tssi_data;
	int init_offset;

	init_offset = -((tssi_db * d->slope + d->offset[1]) / 4096) + 10;

	mt76_rmw(dev, MT_TX_ALC_CFG_1, MT_TX_ALC_CFG_1_TEMP_COMP,
		 int_to_s6(init_offset) & MT_TX_ALC_CFG_1_TEMP_COMP);
}