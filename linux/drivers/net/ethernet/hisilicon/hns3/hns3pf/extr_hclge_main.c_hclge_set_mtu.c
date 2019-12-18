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
struct hnae3_handle {int dummy; } ;
struct hclge_vport {int dummy; } ;

/* Variables and functions */
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int hclge_set_vport_mtu (struct hclge_vport*,int) ; 

__attribute__((used)) static int hclge_set_mtu(struct hnae3_handle *handle, int new_mtu)
{
	struct hclge_vport *vport = hclge_get_vport(handle);

	return hclge_set_vport_mtu(vport, new_mtu);
}