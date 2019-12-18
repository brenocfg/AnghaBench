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
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ OFDPA_INTERNAL_VLAN_ID_BASE ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ofdpa_vlan_id_is_internal(__be16 vlan_id)
{
	u16 start = OFDPA_INTERNAL_VLAN_ID_BASE;
	u16 end = 0xffe;
	u16 _vlan_id = ntohs(vlan_id);

	return (_vlan_id >= start && _vlan_id <= end);
}