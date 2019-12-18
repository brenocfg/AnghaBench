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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {void* len; void* type; } ;
struct mrvl_ie_cf_param_set {TYPE_1__ header; } ;

/* Variables and functions */
 int TLV_TYPE_CF ; 
 void* cpu_to_le16 (int) ; 

__attribute__((used)) static int lbs_add_cf_param_tlv(u8 *tlv)
{
	struct mrvl_ie_cf_param_set *cf = (void *)tlv;

	/*
	 * 04 00  TLV_TYPE_CF
	 * 06 00  len
	 * 00     cfpcnt
	 * 00     cfpperiod
	 * 00 00  cfpmaxduration
	 * 00 00  cfpdurationremaining
	 */
	cf->header.type = cpu_to_le16(TLV_TYPE_CF);
	cf->header.len = cpu_to_le16(sizeof(*cf)-sizeof(cf->header));
	return sizeof(*cf);
}