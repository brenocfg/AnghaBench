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
typedef  scalar_t__ u32 ;
struct mwifiex_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIGURATION_REG ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ MAX_WRITE_IOMEM_RETRY ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 int mwifiex_write_data_sync (struct mwifiex_adapter*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ mwifiex_write_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mwifiex_write_data_to_card(struct mwifiex_adapter *adapter,
				      u8 *payload, u32 pkt_len, u32 port)
{
	u32 i = 0;
	int ret;

	do {
		ret = mwifiex_write_data_sync(adapter, payload, pkt_len, port);
		if (ret) {
			i++;
			mwifiex_dbg(adapter, ERROR,
				    "host_to_card, write iomem\t"
				    "(%d) failed: %d\n", i, ret);
			if (mwifiex_write_reg(adapter, CONFIGURATION_REG, 0x04))
				mwifiex_dbg(adapter, ERROR,
					    "write CFG reg failed\n");

			ret = -1;
			if (i > MAX_WRITE_IOMEM_RETRY)
				return ret;
		}
	} while (ret == -1);

	return ret;
}