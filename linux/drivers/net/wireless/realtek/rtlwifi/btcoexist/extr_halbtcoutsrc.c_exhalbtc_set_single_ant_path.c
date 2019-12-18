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
struct TYPE_2__ {int /*<<< orphan*/  single_ant_path; } ;
struct btc_coexist {TYPE_1__ board_info; } ;

/* Variables and functions */

void exhalbtc_set_single_ant_path(struct btc_coexist *btcoexist,
				  u8 single_ant_path)
{
	btcoexist->board_info.single_ant_path = single_ant_path;
}