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
struct mlxfw_mfa2_tlv_multi {int dummy; } ;
struct mlxfw_mfa2_tlv {int dummy; } ;
struct mlxfw_mfa2_file {int dummy; } ;

/* Variables and functions */
 size_t NLA_ALIGN (int) ; 
 struct mlxfw_mfa2_tlv const* mlxfw_mfa2_tlv_get (struct mlxfw_mfa2_file const*,void*) ; 

const struct mlxfw_mfa2_tlv *
mlxfw_mfa2_tlv_multi_child(const struct mlxfw_mfa2_file *mfa2_file,
			   const struct mlxfw_mfa2_tlv_multi *multi)
{
	size_t multi_len;

	multi_len = NLA_ALIGN(sizeof(struct mlxfw_mfa2_tlv_multi));
	return mlxfw_mfa2_tlv_get(mfa2_file, (void *) multi + multi_len);
}