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
typedef  int u32 ;
struct netxen_adapter {scalar_t__ portnum; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  NETXEN_NON_ULA_ADAPTER_KEY 129 
#define  NETXEN_ULA_ADAPTER_KEY 128 
 int /*<<< orphan*/  NETXEN_ULA_KEY ; 
 int NXRD32 (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void netxen_read_ula_info(struct netxen_adapter *adapter)
{
	u32 temp;

	/* Print ULA info only once for an adapter */
	if (adapter->portnum != 0)
		return;

	temp = NXRD32(adapter, NETXEN_ULA_KEY);
	switch (temp) {
	case NETXEN_ULA_ADAPTER_KEY:
		dev_info(&adapter->pdev->dev, "ULA adapter");
		break;
	case NETXEN_NON_ULA_ADAPTER_KEY:
		dev_info(&adapter->pdev->dev, "non ULA adapter");
		break;
	default:
		break;
	}

	return;
}