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
struct TYPE_2__ {int /*<<< orphan*/  desc_len; int /*<<< orphan*/  desc_type; } ;
struct be_port_res_desc {int flags; int nv_flags; scalar_t__ nv_port; int /*<<< orphan*/  link_num; TYPE_1__ hdr; } ;
struct be_adapter {int /*<<< orphan*/  hba_port_num; } ;
typedef  int /*<<< orphan*/  port_desc ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int IMM_SHIFT ; 
 int NOSV_SHIFT ; 
 int NV_TYPE_DISABLED ; 
 int NV_TYPE_VXLAN ; 
 int /*<<< orphan*/  PORT_RESOURCE_DESC_TYPE_V1 ; 
 int RCVID_SHIFT ; 
 int /*<<< orphan*/  RESOURCE_DESC_SIZE_V1 ; 
 int SOCVID_SHIFT ; 
 int be_cmd_set_profile_config (struct be_adapter*,struct be_port_res_desc*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct be_port_res_desc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ swab16 (scalar_t__) ; 

int be_cmd_set_vxlan_port(struct be_adapter *adapter, __be16 port)
{
	struct be_port_res_desc port_desc;

	memset(&port_desc, 0, sizeof(port_desc));
	port_desc.hdr.desc_type = PORT_RESOURCE_DESC_TYPE_V1;
	port_desc.hdr.desc_len = RESOURCE_DESC_SIZE_V1;
	port_desc.flags = (1 << IMM_SHIFT) | (1 << NOSV_SHIFT);
	port_desc.link_num = adapter->hba_port_num;
	if (port) {
		port_desc.nv_flags = NV_TYPE_VXLAN | (1 << SOCVID_SHIFT) |
					(1 << RCVID_SHIFT);
		port_desc.nv_port = swab16(port);
	} else {
		port_desc.nv_flags = NV_TYPE_DISABLED;
		port_desc.nv_port = 0;
	}

	return be_cmd_set_profile_config(adapter, &port_desc,
					 RESOURCE_DESC_SIZE_V1, 1, 1, 0);
}