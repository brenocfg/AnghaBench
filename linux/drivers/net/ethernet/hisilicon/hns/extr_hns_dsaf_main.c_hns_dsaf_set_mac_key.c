#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  void* u16 ;
struct TYPE_7__ {scalar_t__ port_vlan; void* mac_5; void* mac_4; } ;
struct TYPE_8__ {TYPE_3__ bits; } ;
struct TYPE_5__ {void* mac_3; void* mac_2; void* mac_1; void* mac_0; } ;
struct TYPE_6__ {TYPE_1__ bits; } ;
struct dsaf_drv_tbl_tcam_key {TYPE_4__ low; TYPE_2__ high; } ;
struct dsaf_device {scalar_t__ dsaf_mode; } ;

/* Variables and functions */
 scalar_t__ DSAF_MODE_ENABLE ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_KEY_PORT_M ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_KEY_PORT_S ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_KEY_VLAN_M ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_KEY_VLAN_S ; 
 int /*<<< orphan*/  dsaf_set_field (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void hns_dsaf_set_mac_key(
	struct dsaf_device *dsaf_dev,
	struct dsaf_drv_tbl_tcam_key *mac_key, u16 vlan_id, u8 in_port_num,
	u8 *addr)
{
	u8 port;

	if (dsaf_dev->dsaf_mode <= DSAF_MODE_ENABLE)
		/*DSAF mode : in port id fixed 0*/
		port = 0;
	else
		/*non-dsaf mode*/
		port = in_port_num;

	mac_key->high.bits.mac_0 = addr[0];
	mac_key->high.bits.mac_1 = addr[1];
	mac_key->high.bits.mac_2 = addr[2];
	mac_key->high.bits.mac_3 = addr[3];
	mac_key->low.bits.mac_4 = addr[4];
	mac_key->low.bits.mac_5 = addr[5];
	mac_key->low.bits.port_vlan = 0;
	dsaf_set_field(mac_key->low.bits.port_vlan, DSAF_TBL_TCAM_KEY_VLAN_M,
		       DSAF_TBL_TCAM_KEY_VLAN_S, vlan_id);
	dsaf_set_field(mac_key->low.bits.port_vlan, DSAF_TBL_TCAM_KEY_PORT_M,
		       DSAF_TBL_TCAM_KEY_PORT_S, port);
}