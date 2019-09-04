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
struct pkcs7_signed_info {int unsupported_crypto; scalar_t__ blacklisted; struct pkcs7_signed_info* next; } ;
struct pkcs7_message {struct pkcs7_signed_info* signed_infos; int /*<<< orphan*/  data_type; int /*<<< orphan*/  have_authattrs; } ;
typedef  enum key_being_used_for { ____Placeholder_key_being_used_for } key_being_used_for ;

/* Variables and functions */
 int EINVAL ; 
 int EKEYREJECTED ; 
 int ENOPKG ; 
 int /*<<< orphan*/  OID_data ; 
 int /*<<< orphan*/  OID_msIndirectData ; 
#define  VERIFYING_FIRMWARE_SIGNATURE 131 
#define  VERIFYING_KEXEC_PE_SIGNATURE 130 
#define  VERIFYING_MODULE_SIGNATURE 129 
#define  VERIFYING_UNSPECIFIED_SIGNATURE 128 
 int /*<<< orphan*/  kenter (char*) ; 
 int /*<<< orphan*/  kleave (char*,int) ; 
 int pkcs7_verify_one (struct pkcs7_message*,struct pkcs7_signed_info*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

int pkcs7_verify(struct pkcs7_message *pkcs7,
		 enum key_being_used_for usage)
{
	struct pkcs7_signed_info *sinfo;
	int actual_ret = -ENOPKG;
	int ret;

	kenter("");

	switch (usage) {
	case VERIFYING_MODULE_SIGNATURE:
		if (pkcs7->data_type != OID_data) {
			pr_warn("Invalid module sig (not pkcs7-data)\n");
			return -EKEYREJECTED;
		}
		if (pkcs7->have_authattrs) {
			pr_warn("Invalid module sig (has authattrs)\n");
			return -EKEYREJECTED;
		}
		break;
	case VERIFYING_FIRMWARE_SIGNATURE:
		if (pkcs7->data_type != OID_data) {
			pr_warn("Invalid firmware sig (not pkcs7-data)\n");
			return -EKEYREJECTED;
		}
		if (!pkcs7->have_authattrs) {
			pr_warn("Invalid firmware sig (missing authattrs)\n");
			return -EKEYREJECTED;
		}
		break;
	case VERIFYING_KEXEC_PE_SIGNATURE:
		if (pkcs7->data_type != OID_msIndirectData) {
			pr_warn("Invalid kexec sig (not Authenticode)\n");
			return -EKEYREJECTED;
		}
		/* Authattr presence checked in parser */
		break;
	case VERIFYING_UNSPECIFIED_SIGNATURE:
		if (pkcs7->data_type != OID_data) {
			pr_warn("Invalid unspecified sig (not pkcs7-data)\n");
			return -EKEYREJECTED;
		}
		break;
	default:
		return -EINVAL;
	}

	for (sinfo = pkcs7->signed_infos; sinfo; sinfo = sinfo->next) {
		ret = pkcs7_verify_one(pkcs7, sinfo);
		if (sinfo->blacklisted) {
			if (actual_ret == -ENOPKG)
				actual_ret = -EKEYREJECTED;
			continue;
		}
		if (ret < 0) {
			if (ret == -ENOPKG) {
				sinfo->unsupported_crypto = true;
				continue;
			}
			kleave(" = %d", ret);
			return ret;
		}
		actual_ret = 0;
	}

	kleave(" = %d", actual_ret);
	return actual_ret;
}