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
struct vnic_login_client_data {int dummy; } ;
struct ibmvnic_adapter {TYPE_1__* netdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  nodename; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 TYPE_2__* utsname () ; 

__attribute__((used)) static int vnic_client_data_len(struct ibmvnic_adapter *adapter)
{
	int len;

	/* Calculate the amount of buffer space needed for the
	 * vnic client data in the login buffer. There are four entries,
	 * OS name, LPAR name, device name, and a null last entry.
	 */
	len = 4 * sizeof(struct vnic_login_client_data);
	len += 6; /* "Linux" plus NULL */
	len += strlen(utsname()->nodename) + 1;
	len += strlen(adapter->netdev->name) + 1;

	return len;
}