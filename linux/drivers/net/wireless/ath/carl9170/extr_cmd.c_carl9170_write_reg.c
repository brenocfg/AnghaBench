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
typedef  int /*<<< orphan*/  u32 ;
struct ar9170 {TYPE_1__* hw; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_CMD_WREG ; 
 int carl9170_exec_cmd (struct ar9170*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const cpu_to_le32 (int /*<<< orphan*/  const) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int) ; 

int carl9170_write_reg(struct ar9170 *ar, const u32 reg, const u32 val)
{
	const __le32 buf[2] = {
		cpu_to_le32(reg),
		cpu_to_le32(val),
	};
	int err;

	err = carl9170_exec_cmd(ar, CARL9170_CMD_WREG, sizeof(buf),
				(u8 *) buf, 0, NULL);
	if (err) {
		if (net_ratelimit()) {
			wiphy_err(ar->hw->wiphy, "writing reg %#x "
				"(val %#x) failed (%d)\n", reg, val, err);
		}
	}
	return err;
}