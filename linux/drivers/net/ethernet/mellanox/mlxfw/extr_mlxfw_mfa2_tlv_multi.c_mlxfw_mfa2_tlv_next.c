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
typedef  int u16 ;
struct mlxfw_mfa2_tlv_multi {int /*<<< orphan*/  total_len; } ;
struct mlxfw_mfa2_tlv {scalar_t__ type; } ;
struct mlxfw_mfa2_file {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLXFW_MFA2_TLV_MULTI_PART ; 
 int MLXFW_MFA2_TLV_TOTAL_SIZE (struct mlxfw_mfa2_tlv const*) ; 
 int NLA_ALIGN (int) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct mlxfw_mfa2_tlv const* mlxfw_mfa2_tlv_get (struct mlxfw_mfa2_file const*,void*) ; 
 struct mlxfw_mfa2_tlv_multi* mlxfw_mfa2_tlv_multi_get (struct mlxfw_mfa2_file const*,struct mlxfw_mfa2_tlv const*) ; 

const struct mlxfw_mfa2_tlv *
mlxfw_mfa2_tlv_next(const struct mlxfw_mfa2_file *mfa2_file,
		    const struct mlxfw_mfa2_tlv *tlv)
{
	const struct mlxfw_mfa2_tlv_multi *multi;
	u16 tlv_len;
	void *next;

	tlv_len = MLXFW_MFA2_TLV_TOTAL_SIZE(tlv);

	if (tlv->type == MLXFW_MFA2_TLV_MULTI_PART) {
		multi = mlxfw_mfa2_tlv_multi_get(mfa2_file, tlv);
		tlv_len = NLA_ALIGN(tlv_len + be16_to_cpu(multi->total_len));
	}

	next = (void *) tlv + tlv_len;
	return mlxfw_mfa2_tlv_get(mfa2_file, next);
}