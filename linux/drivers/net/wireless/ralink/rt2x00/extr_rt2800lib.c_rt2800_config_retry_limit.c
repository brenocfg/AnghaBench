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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00lib_conf {TYPE_1__* conf; } ;
struct rt2x00_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  long_frame_max_tx_count; int /*<<< orphan*/  short_frame_max_tx_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_RTY_CFG ; 
 int /*<<< orphan*/  TX_RTY_CFG_LONG_RTY_LIMIT ; 
 int /*<<< orphan*/  TX_RTY_CFG_SHORT_RTY_LIMIT ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2800_config_retry_limit(struct rt2x00_dev *rt2x00dev,
				      struct rt2x00lib_conf *libconf)
{
	u32 reg;

	reg = rt2800_register_read(rt2x00dev, TX_RTY_CFG);
	rt2x00_set_field32(&reg, TX_RTY_CFG_SHORT_RTY_LIMIT,
			   libconf->conf->short_frame_max_tx_count);
	rt2x00_set_field32(&reg, TX_RTY_CFG_LONG_RTY_LIMIT,
			   libconf->conf->long_frame_max_tx_count);
	rt2800_register_write(rt2x00dev, TX_RTY_CFG, reg);
}