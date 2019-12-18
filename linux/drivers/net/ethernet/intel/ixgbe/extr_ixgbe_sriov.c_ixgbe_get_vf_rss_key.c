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
typedef  size_t u32 ;
struct ixgbe_adapter {int /*<<< orphan*/  rss_key; TYPE_1__* vfinfo; } ;
struct TYPE_2__ {int vf_api; int /*<<< orphan*/  rss_query_enabled; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  IXGBE_RSS_KEY_SIZE ; 
#define  ixgbe_mbox_api_12 130 
#define  ixgbe_mbox_api_13 129 
#define  ixgbe_mbox_api_14 128 
 int /*<<< orphan*/  memcpy (size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ixgbe_get_vf_rss_key(struct ixgbe_adapter *adapter,
				u32 *msgbuf, u32 vf)
{
	u32 *rss_key = &msgbuf[1];

	/* Check if the operation is permitted */
	if (!adapter->vfinfo[vf].rss_query_enabled)
		return -EPERM;

	/* verify the PF is supporting the correct API */
	switch (adapter->vfinfo[vf].vf_api) {
	case ixgbe_mbox_api_14:
	case ixgbe_mbox_api_13:
	case ixgbe_mbox_api_12:
		break;
	default:
		return -EOPNOTSUPP;
	}

	memcpy(rss_key, adapter->rss_key, IXGBE_RSS_KEY_SIZE);

	return 0;
}