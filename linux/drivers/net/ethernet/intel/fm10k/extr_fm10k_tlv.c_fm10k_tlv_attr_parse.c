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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct fm10k_tlv_attr {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ FM10K_ERR_PARAM ; 
 scalar_t__ FM10K_NOT_IMPLEMENTED ; 
 size_t FM10K_TLV_DWORD_LEN (size_t) ; 
 size_t FM10K_TLV_ID_MASK ; 
 size_t FM10K_TLV_LEN_SHIFT ; 
 size_t FM10K_TLV_RESULTS_MAX ; 
 scalar_t__ fm10k_tlv_attr_validate (size_t*,struct fm10k_tlv_attr const*) ; 

__attribute__((used)) static s32 fm10k_tlv_attr_parse(u32 *attr, u32 **results,
				const struct fm10k_tlv_attr *tlv_attr)
{
	u32 i, attr_id, offset = 0;
	s32 err;
	u16 len;

	/* verify pointers are not NULL */
	if (!attr || !results)
		return FM10K_ERR_PARAM;

	/* initialize results to NULL */
	for (i = 0; i < FM10K_TLV_RESULTS_MAX; i++)
		results[i] = NULL;

	/* pull length from the message header */
	len = *attr >> FM10K_TLV_LEN_SHIFT;

	/* no attributes to parse if there is no length */
	if (!len)
		return 0;

	/* no attributes to parse, just raw data, message becomes attribute */
	if (!tlv_attr) {
		results[0] = attr;
		return 0;
	}

	/* move to start of attribute data */
	attr++;

	/* run through list parsing all attributes */
	while (offset < len) {
		attr_id = *attr & FM10K_TLV_ID_MASK;

		if (attr_id >= FM10K_TLV_RESULTS_MAX)
			return FM10K_NOT_IMPLEMENTED;

		err = fm10k_tlv_attr_validate(attr, tlv_attr);
		if (err == FM10K_NOT_IMPLEMENTED)
			; /* silently ignore non-implemented attributes */
		else if (err)
			return err;
		else
			results[attr_id] = attr;

		/* update offset */
		offset += FM10K_TLV_DWORD_LEN(*attr) * 4;

		/* move to next attribute */
		attr = &attr[FM10K_TLV_DWORD_LEN(*attr)];
	}

	/* we should find ourselves at the end of the list */
	if (offset != len)
		return FM10K_ERR_PARAM;

	return 0;
}