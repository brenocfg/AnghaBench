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
struct mrvl_ie_rates_param_set {TYPE_1__ header; } ;

/* Variables and functions */
 size_t TLV_TYPE_RATES ; 
 void* cpu_to_le16 (size_t) ; 
 size_t lbs_add_rates (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lbs_add_supported_rates_tlv(u8 *tlv)
{
	size_t i;
	struct mrvl_ie_rates_param_set *rate_tlv = (void *)tlv;

	/*
	 * TLV-ID RATES  01 00
	 * length        0e 00
	 * rates         82 84 8b 96 0c 12 18 24 30 48 60 6c
	 */
	rate_tlv->header.type = cpu_to_le16(TLV_TYPE_RATES);
	tlv += sizeof(rate_tlv->header);
	i = lbs_add_rates(tlv);
	tlv += i;
	rate_tlv->header.len = cpu_to_le16(i);
	return sizeof(rate_tlv->header) + i;
}