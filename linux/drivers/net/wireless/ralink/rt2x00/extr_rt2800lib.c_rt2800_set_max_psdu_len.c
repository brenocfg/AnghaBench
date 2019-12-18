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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {struct rt2800_drv_data* drv_data; } ;
struct rt2800_drv_data {scalar_t__* ampdu_factor_cnt; int /*<<< orphan*/  max_psdu; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_LEN_CFG ; 
 int /*<<< orphan*/  MAX_LEN_CFG_MAX_PSDU ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2800_set_max_psdu_len(struct rt2x00_dev *rt2x00dev)
{
	u8 i, max_psdu;
	u32 reg;
	struct rt2800_drv_data *drv_data = rt2x00dev->drv_data;

	for (i = 0; i < 3; i++)
		if (drv_data->ampdu_factor_cnt[i] > 0)
			break;

	max_psdu = min(drv_data->max_psdu, i);

	reg = rt2800_register_read(rt2x00dev, MAX_LEN_CFG);
	rt2x00_set_field32(&reg, MAX_LEN_CFG_MAX_PSDU, max_psdu);
	rt2800_register_write(rt2x00dev, MAX_LEN_CFG, reg);
}