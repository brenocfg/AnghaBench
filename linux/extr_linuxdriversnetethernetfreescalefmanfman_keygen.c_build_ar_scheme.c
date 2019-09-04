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
typedef  scalar_t__ u8 ;
typedef  int u32 ;

/* Variables and functions */
 int DUMMY_PORT_ID ; 
 int FM_KG_KGAR_GO ; 
 int FM_KG_KGAR_NUM_SHIFT ; 
 scalar_t__ FM_KG_KGAR_READ ; 
 int FM_KG_KGAR_SCM_WSEL_UPDATE_CNT ; 
 int FM_KG_KGAR_SEL_SCHEME_ENTRY ; 
 scalar_t__ FM_KG_KGAR_WRITE ; 

__attribute__((used)) static u32 build_ar_scheme(u8 scheme_id, bool update_counter, bool write)
{
	u32 rw = (u32)(write ? FM_KG_KGAR_WRITE : FM_KG_KGAR_READ);

	return (u32)(FM_KG_KGAR_GO |
			rw |
			FM_KG_KGAR_SEL_SCHEME_ENTRY |
			DUMMY_PORT_ID |
			((u32)scheme_id << FM_KG_KGAR_NUM_SHIFT) |
			(update_counter ? FM_KG_KGAR_SCM_WSEL_UPDATE_CNT : 0));
}