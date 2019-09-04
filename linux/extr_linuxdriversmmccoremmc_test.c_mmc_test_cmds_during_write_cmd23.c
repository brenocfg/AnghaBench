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
struct mmc_test_card {int dummy; } ;

/* Variables and functions */
 int mmc_test_cmds_during_tfr (struct mmc_test_card*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_test_cmds_during_write_cmd23(struct mmc_test_card *test)
{
	return mmc_test_cmds_during_tfr(test, 1, 1, 0);
}