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
typedef  scalar_t__ const u32 ;
struct ar9170 {TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_CMD_ECHO ; 
 int EINVAL ; 
 int carl9170_exec_cmd (struct ar9170*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_info (int /*<<< orphan*/ ,char*,scalar_t__ const,scalar_t__ const) ; 

int carl9170_echo_test(struct ar9170 *ar, const u32 v)
{
	u32 echores;
	int err;

	err = carl9170_exec_cmd(ar, CARL9170_CMD_ECHO,
				4, (u8 *)&v,
				4, (u8 *)&echores);
	if (err)
		return err;

	if (v != echores) {
		wiphy_info(ar->hw->wiphy, "wrong echo %x != %x", v, echores);
		return -EINVAL;
	}

	return 0;
}