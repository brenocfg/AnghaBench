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
struct pkcs7_parse_context {size_t raw_serial_size; void const* raw_serial; } ;

/* Variables and functions */

int pkcs7_sig_note_serial(void *context, size_t hdrlen,
			  unsigned char tag,
			  const void *value, size_t vlen)
{
	struct pkcs7_parse_context *ctx = context;
	ctx->raw_serial = value;
	ctx->raw_serial_size = vlen;
	return 0;
}