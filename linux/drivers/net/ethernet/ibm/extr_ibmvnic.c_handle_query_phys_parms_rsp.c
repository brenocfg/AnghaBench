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
struct TYPE_3__ {int code; } ;
struct TYPE_4__ {int flags1; TYPE_1__ rc; int /*<<< orphan*/  speed; } ;
union ibmvnic_crq {TYPE_2__ query_phys_parms_rsp; } ;
struct net_device {int dummy; } ;
struct ibmvnic_adapter {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; struct net_device* netdev; } ;
typedef  int __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
#define  IBMVNIC_100GBPS 135 
#define  IBMVNIC_100MBPS 134 
#define  IBMVNIC_10GBP 133 
#define  IBMVNIC_10MBPS 132 
#define  IBMVNIC_1GBPS 131 
#define  IBMVNIC_25GBPS 130 
#define  IBMVNIC_40GBPS 129 
#define  IBMVNIC_50GBPS 128 
 int IBMVNIC_FULL_DUPLEX ; 
 int IBMVNIC_HALF_DUPLEX ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int /*<<< orphan*/  SPEED_100000 ; 
 int /*<<< orphan*/  SPEED_25000 ; 
 int /*<<< orphan*/  SPEED_40000 ; 
 int /*<<< orphan*/  SPEED_50000 ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 

__attribute__((used)) static int handle_query_phys_parms_rsp(union ibmvnic_crq *crq,
				       struct ibmvnic_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int rc;
	__be32 rspeed = cpu_to_be32(crq->query_phys_parms_rsp.speed);

	rc = crq->query_phys_parms_rsp.rc.code;
	if (rc) {
		netdev_err(netdev, "Error %d in QUERY_PHYS_PARMS\n", rc);
		return rc;
	}
	switch (rspeed) {
	case IBMVNIC_10MBPS:
		adapter->speed = SPEED_10;
		break;
	case IBMVNIC_100MBPS:
		adapter->speed = SPEED_100;
		break;
	case IBMVNIC_1GBPS:
		adapter->speed = SPEED_1000;
		break;
	case IBMVNIC_10GBP:
		adapter->speed = SPEED_10000;
		break;
	case IBMVNIC_25GBPS:
		adapter->speed = SPEED_25000;
		break;
	case IBMVNIC_40GBPS:
		adapter->speed = SPEED_40000;
		break;
	case IBMVNIC_50GBPS:
		adapter->speed = SPEED_50000;
		break;
	case IBMVNIC_100GBPS:
		adapter->speed = SPEED_100000;
		break;
	default:
		if (netif_carrier_ok(netdev))
			netdev_warn(netdev, "Unknown speed 0x%08x\n", rspeed);
		adapter->speed = SPEED_UNKNOWN;
	}
	if (crq->query_phys_parms_rsp.flags1 & IBMVNIC_FULL_DUPLEX)
		adapter->duplex = DUPLEX_FULL;
	else if (crq->query_phys_parms_rsp.flags1 & IBMVNIC_HALF_DUPLEX)
		adapter->duplex = DUPLEX_HALF;
	else
		adapter->duplex = DUPLEX_UNKNOWN;

	return rc;
}