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
struct hso_device {int dummy; } ;

/* Variables and functions */
 int HSO_MAX_NET_DEVICES ; 
 struct hso_device** network_table ; 

__attribute__((used)) static int remove_net_device(struct hso_device *hso_dev)
{
	int i;

	for (i = 0; i < HSO_MAX_NET_DEVICES; i++) {
		if (network_table[i] == hso_dev) {
			network_table[i] = NULL;
			break;
		}
	}
	if (i == HSO_MAX_NET_DEVICES)
		return -1;
	return 0;
}