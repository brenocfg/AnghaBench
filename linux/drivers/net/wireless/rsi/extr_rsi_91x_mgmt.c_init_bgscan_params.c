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
struct TYPE_2__ {int two_probe; int /*<<< orphan*/  passive_scan_duration; int /*<<< orphan*/  active_scan_duration; scalar_t__ num_bgscan_channels; int /*<<< orphan*/  bgscan_periodicity; int /*<<< orphan*/  roam_threshold; int /*<<< orphan*/  bgscan_threshold; } ;
struct rsi_common {TYPE_1__ bgscan; } ;
struct rsi_bgscan_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSI_ACTIVE_SCAN_TIME ; 
 int /*<<< orphan*/  RSI_BGSCAN_PERIODICITY ; 
 int /*<<< orphan*/  RSI_DEF_BGSCAN_THRLD ; 
 int /*<<< orphan*/  RSI_DEF_ROAM_THRLD ; 
 int /*<<< orphan*/  RSI_PASSIVE_SCAN_TIME ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void init_bgscan_params(struct rsi_common *common)
{
	memset((u8 *)&common->bgscan, 0, sizeof(struct rsi_bgscan_params));
	common->bgscan.bgscan_threshold = RSI_DEF_BGSCAN_THRLD;
	common->bgscan.roam_threshold = RSI_DEF_ROAM_THRLD;
	common->bgscan.bgscan_periodicity = RSI_BGSCAN_PERIODICITY;
	common->bgscan.num_bgscan_channels = 0;
	common->bgscan.two_probe = 1;
	common->bgscan.active_scan_duration = RSI_ACTIVE_SCAN_TIME;
	common->bgscan.passive_scan_duration = RSI_PASSIVE_SCAN_TIME;
}