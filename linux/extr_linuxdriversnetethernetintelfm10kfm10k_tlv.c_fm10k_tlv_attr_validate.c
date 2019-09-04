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
typedef  int u32 ;
typedef  int u16 ;
struct fm10k_tlv_attr {int id; int type; int len; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 int /*<<< orphan*/  FM10K_NOT_IMPLEMENTED ; 
#define  FM10K_TLV_BOOL 134 
 int FM10K_TLV_FLAGS_MSG ; 
 int FM10K_TLV_FLAGS_SHIFT ; 
 int FM10K_TLV_ID_MASK ; 
 int FM10K_TLV_LEN_SHIFT ; 
#define  FM10K_TLV_LE_STRUCT 133 
#define  FM10K_TLV_MAC_ADDR 132 
#define  FM10K_TLV_NESTED 131 
#define  FM10K_TLV_NULL_STRING 130 
#define  FM10K_TLV_SIGNED 129 
#define  FM10K_TLV_UNSIGNED 128 

__attribute__((used)) static s32 fm10k_tlv_attr_validate(u32 *attr,
				   const struct fm10k_tlv_attr *tlv_attr)
{
	u32 attr_id = *attr & FM10K_TLV_ID_MASK;
	u16 len = *attr >> FM10K_TLV_LEN_SHIFT;

	/* verify this is an attribute and not a message */
	if (*attr & (FM10K_TLV_FLAGS_MSG << FM10K_TLV_FLAGS_SHIFT))
		return FM10K_ERR_PARAM;

	/* search through the list of attributes to find a matching ID */
	while (tlv_attr->id < attr_id)
		tlv_attr++;

	/* if didn't find a match then we should exit */
	if (tlv_attr->id != attr_id)
		return FM10K_NOT_IMPLEMENTED;

	/* move to start of attribute data */
	attr++;

	switch (tlv_attr->type) {
	case FM10K_TLV_NULL_STRING:
		if (!len ||
		    (attr[(len - 1) / 4] & (0xFF << (8 * ((len - 1) % 4)))))
			return FM10K_ERR_PARAM;
		if (len > tlv_attr->len)
			return FM10K_ERR_PARAM;
		break;
	case FM10K_TLV_MAC_ADDR:
		if (len != ETH_ALEN)
			return FM10K_ERR_PARAM;
		break;
	case FM10K_TLV_BOOL:
		if (len)
			return FM10K_ERR_PARAM;
		break;
	case FM10K_TLV_UNSIGNED:
	case FM10K_TLV_SIGNED:
		if (len != tlv_attr->len)
			return FM10K_ERR_PARAM;
		break;
	case FM10K_TLV_LE_STRUCT:
		/* struct must be 4 byte aligned */
		if ((len % 4) || len != tlv_attr->len)
			return FM10K_ERR_PARAM;
		break;
	case FM10K_TLV_NESTED:
		/* nested attributes must be 4 byte aligned */
		if (len % 4)
			return FM10K_ERR_PARAM;
		break;
	default:
		/* attribute id is mapped to bad value */
		return FM10K_ERR_PARAM;
	}

	return 0;
}