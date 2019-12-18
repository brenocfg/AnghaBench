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
struct TYPE_2__ {int /*<<< orphan*/ * svc_map; } ;
struct ath10k {TYPE_1__ wmi; int /*<<< orphan*/  dev_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_FLAG_PEER_STATS ; 
 int /*<<< orphan*/  WMI_SERVICE_PEER_STATS ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool ath10k_peer_stats_enabled(struct ath10k *ar)
{
	if (test_bit(ATH10K_FLAG_PEER_STATS, &ar->dev_flags) &&
	    test_bit(WMI_SERVICE_PEER_STATS, ar->wmi.svc_map))
		return true;

	return false;
}