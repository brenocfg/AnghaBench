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
struct pkcs7_parse_context {scalar_t__ last_oid; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ OID_signed_data ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

int pkcs7_check_content_type(void *context, size_t hdrlen,
			     unsigned char tag,
			     const void *value, size_t vlen)
{
	struct pkcs7_parse_context *ctx = context;

	if (ctx->last_oid != OID_signed_data) {
		pr_warn("Only support pkcs7_signedData type\n");
		return -EINVAL;
	}

	return 0;
}