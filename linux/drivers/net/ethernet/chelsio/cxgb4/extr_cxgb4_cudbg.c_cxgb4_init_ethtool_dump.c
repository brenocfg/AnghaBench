#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/  version; int /*<<< orphan*/  flag; } ;
struct TYPE_3__ {int /*<<< orphan*/  fw_vers; } ;
struct adapter {TYPE_2__ eth_dump; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXGB4_ETH_DUMP_NONE ; 

void cxgb4_init_ethtool_dump(struct adapter *adapter)
{
	adapter->eth_dump.flag = CXGB4_ETH_DUMP_NONE;
	adapter->eth_dump.version = adapter->params.fw_vers;
	adapter->eth_dump.len = 0;
}