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
struct wsm_configuration {TYPE_1__* txPowerRange; void* supportedRateMask; int /*<<< orphan*/  dot11FrequencyBandsSupported; int /*<<< orphan*/  dot11StationId; } ;
struct wsm_buf {int dummy; } ;
struct cw1200_common {int dummy; } ;
struct TYPE_2__ {void* stepping; void* max_power_level; void* min_power_level; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WSM_GET (struct wsm_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* WSM_GET32 (struct wsm_buf*) ; 
 int /*<<< orphan*/  WSM_GET8 (struct wsm_buf*) ; 
 int /*<<< orphan*/  WSM_SKIP (struct wsm_buf*,int) ; 
 int WSM_STATUS_SUCCESS ; 

__attribute__((used)) static int wsm_configuration_confirm(struct cw1200_common *priv,
				     struct wsm_configuration *arg,
				     struct wsm_buf *buf)
{
	int i;
	int status;

	status = WSM_GET32(buf);
	if (WARN_ON(status != WSM_STATUS_SUCCESS))
		return -EINVAL;

	WSM_GET(buf, arg->dot11StationId, ETH_ALEN);
	arg->dot11FrequencyBandsSupported = WSM_GET8(buf);
	WSM_SKIP(buf, 1);
	arg->supportedRateMask = WSM_GET32(buf);
	for (i = 0; i < 2; ++i) {
		arg->txPowerRange[i].min_power_level = WSM_GET32(buf);
		arg->txPowerRange[i].max_power_level = WSM_GET32(buf);
		arg->txPowerRange[i].stepping = WSM_GET32(buf);
	}
	return 0;

underflow:
	WARN_ON(1);
	return -EINVAL;
}