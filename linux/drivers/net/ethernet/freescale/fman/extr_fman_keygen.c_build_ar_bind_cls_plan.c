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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int FM_KG_KGAR_GO ; 
 scalar_t__ FM_KG_KGAR_READ ; 
 int FM_KG_KGAR_SEL_PORT_ENTRY ; 
 int FM_KG_KGAR_SEL_PORT_WSEL_CPP ; 
 scalar_t__ FM_KG_KGAR_WRITE ; 

__attribute__((used)) static u32 build_ar_bind_cls_plan(u8 hwport_id, bool write)
{
	u32 rw = write ? (u32)FM_KG_KGAR_WRITE : (u32)FM_KG_KGAR_READ;

	return (u32)(FM_KG_KGAR_GO |
			rw |
			FM_KG_KGAR_SEL_PORT_ENTRY |
			hwport_id |
			FM_KG_KGAR_SEL_PORT_WSEL_CPP);
}