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
struct zcrypt_queue {int dummy; } ;
struct TYPE_2__ {int msg_len; void* msg_type_code; } ;
struct type50_meb3_msg {unsigned char* modulus; unsigned char* exponent; unsigned char* message; int /*<<< orphan*/  keyblock_type; TYPE_1__ header; } ;
struct type50_meb2_msg {unsigned char* modulus; unsigned char* exponent; unsigned char* message; int /*<<< orphan*/  keyblock_type; TYPE_1__ header; } ;
struct type50_meb1_msg {unsigned char* modulus; unsigned char* exponent; unsigned char* message; int /*<<< orphan*/  keyblock_type; TYPE_1__ header; } ;
struct ica_rsa_modexpo {int inputdatalength; int /*<<< orphan*/  inputdata; int /*<<< orphan*/  b_key; int /*<<< orphan*/  n_modulus; } ;
struct ap_message {int length; struct type50_meb3_msg* message; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  TYPE50_MEB1_FMT ; 
 int /*<<< orphan*/  TYPE50_MEB2_FMT ; 
 int /*<<< orphan*/  TYPE50_MEB3_FMT ; 
 void* TYPE50_TYPE_CODE ; 
 scalar_t__ copy_from_user (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct type50_meb3_msg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ICAMEX_msg_to_type50MEX_msg(struct zcrypt_queue *zq,
				       struct ap_message *ap_msg,
				       struct ica_rsa_modexpo *mex)
{
	unsigned char *mod, *exp, *inp;
	int mod_len;

	mod_len = mex->inputdatalength;

	if (mod_len <= 128) {
		struct type50_meb1_msg *meb1 = ap_msg->message;

		memset(meb1, 0, sizeof(*meb1));
		ap_msg->length = sizeof(*meb1);
		meb1->header.msg_type_code = TYPE50_TYPE_CODE;
		meb1->header.msg_len = sizeof(*meb1);
		meb1->keyblock_type = TYPE50_MEB1_FMT;
		mod = meb1->modulus + sizeof(meb1->modulus) - mod_len;
		exp = meb1->exponent + sizeof(meb1->exponent) - mod_len;
		inp = meb1->message + sizeof(meb1->message) - mod_len;
	} else if (mod_len <= 256) {
		struct type50_meb2_msg *meb2 = ap_msg->message;

		memset(meb2, 0, sizeof(*meb2));
		ap_msg->length = sizeof(*meb2);
		meb2->header.msg_type_code = TYPE50_TYPE_CODE;
		meb2->header.msg_len = sizeof(*meb2);
		meb2->keyblock_type = TYPE50_MEB2_FMT;
		mod = meb2->modulus + sizeof(meb2->modulus) - mod_len;
		exp = meb2->exponent + sizeof(meb2->exponent) - mod_len;
		inp = meb2->message + sizeof(meb2->message) - mod_len;
	} else if (mod_len <= 512) {
		struct type50_meb3_msg *meb3 = ap_msg->message;

		memset(meb3, 0, sizeof(*meb3));
		ap_msg->length = sizeof(*meb3);
		meb3->header.msg_type_code = TYPE50_TYPE_CODE;
		meb3->header.msg_len = sizeof(*meb3);
		meb3->keyblock_type = TYPE50_MEB3_FMT;
		mod = meb3->modulus + sizeof(meb3->modulus) - mod_len;
		exp = meb3->exponent + sizeof(meb3->exponent) - mod_len;
		inp = meb3->message + sizeof(meb3->message) - mod_len;
	} else
		return -EINVAL;

	if (copy_from_user(mod, mex->n_modulus, mod_len) ||
	    copy_from_user(exp, mex->b_key, mod_len) ||
	    copy_from_user(inp, mex->inputdata, mod_len))
		return -EFAULT;
	return 0;
}