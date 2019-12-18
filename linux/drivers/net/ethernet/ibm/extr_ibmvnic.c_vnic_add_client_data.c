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
struct vnic_login_client_data {int type; scalar_t__ name; void* len; } ;
struct ibmvnic_adapter {TYPE_1__* netdev; } ;
struct TYPE_4__ {char const* nodename; } ;
struct TYPE_3__ {char const* name; } ;

/* Variables and functions */
 void* cpu_to_be16 (int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (scalar_t__,char const*,int) ; 
 TYPE_2__* utsname () ; 

__attribute__((used)) static void vnic_add_client_data(struct ibmvnic_adapter *adapter,
				 struct vnic_login_client_data *vlcd)
{
	const char *os_name = "Linux";
	int len;

	/* Type 1 - LPAR OS */
	vlcd->type = 1;
	len = strlen(os_name) + 1;
	vlcd->len = cpu_to_be16(len);
	strncpy(vlcd->name, os_name, len);
	vlcd = (struct vnic_login_client_data *)(vlcd->name + len);

	/* Type 2 - LPAR name */
	vlcd->type = 2;
	len = strlen(utsname()->nodename) + 1;
	vlcd->len = cpu_to_be16(len);
	strncpy(vlcd->name, utsname()->nodename, len);
	vlcd = (struct vnic_login_client_data *)(vlcd->name + len);

	/* Type 3 - device name */
	vlcd->type = 3;
	len = strlen(adapter->netdev->name) + 1;
	vlcd->len = cpu_to_be16(len);
	strncpy(vlcd->name, adapter->netdev->name, len);
}