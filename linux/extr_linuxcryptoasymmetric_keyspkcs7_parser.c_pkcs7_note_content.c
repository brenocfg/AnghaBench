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
struct pkcs7_parse_context {scalar_t__ last_oid; TYPE_1__* msg; } ;
struct TYPE_2__ {scalar_t__ data_type; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ OID_data ; 
 scalar_t__ OID_msIndirectData ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__) ; 

int pkcs7_note_content(void *context, size_t hdrlen,
		       unsigned char tag,
		       const void *value, size_t vlen)
{
	struct pkcs7_parse_context *ctx = context;

	if (ctx->last_oid != OID_data &&
	    ctx->last_oid != OID_msIndirectData) {
		pr_warn("Unsupported data type %d\n", ctx->last_oid);
		return -EINVAL;
	}

	ctx->msg->data_type = ctx->last_oid;
	return 0;
}