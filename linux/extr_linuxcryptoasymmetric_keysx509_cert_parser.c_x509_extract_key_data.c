#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct x509_parse_context {scalar_t__ last_oid; size_t key_size; void const* key; TYPE_2__* cert; } ;
struct TYPE_4__ {TYPE_1__* pub; } ;
struct TYPE_3__ {char* pkey_algo; } ;

/* Variables and functions */
 int EBADMSG ; 
 int ENOPKG ; 
 scalar_t__ OID_rsaEncryption ; 

int x509_extract_key_data(void *context, size_t hdrlen,
			  unsigned char tag,
			  const void *value, size_t vlen)
{
	struct x509_parse_context *ctx = context;

	if (ctx->last_oid != OID_rsaEncryption)
		return -ENOPKG;

	ctx->cert->pub->pkey_algo = "rsa";

	/* Discard the BIT STRING metadata */
	if (vlen < 1 || *(const u8 *)value != 0)
		return -EBADMSG;
	ctx->key = value + 1;
	ctx->key_size = vlen - 1;
	return 0;
}