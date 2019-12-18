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
struct hts221_hw {int /*<<< orphan*/  regmap; } ;
typedef  int s16 ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int IIO_VAL_INT ; 
 int hts221_set_enable (struct hts221_hw*,int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hts221_read_oneshot(struct hts221_hw *hw, u8 addr, int *val)
{
	__le16 data;
	int err;

	err = hts221_set_enable(hw, true);
	if (err < 0)
		return err;

	msleep(50);

	err = regmap_bulk_read(hw->regmap, addr, &data, sizeof(data));
	if (err < 0)
		return err;

	hts221_set_enable(hw, false);

	*val = (s16)le16_to_cpu(data);

	return IIO_VAL_INT;
}