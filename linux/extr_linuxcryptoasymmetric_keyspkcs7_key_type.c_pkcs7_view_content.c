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
struct key_preparsed_payload {void* data; size_t datalen; } ;

/* Variables and functions */
 int user_preparse (struct key_preparsed_payload*) ; 

__attribute__((used)) static int pkcs7_view_content(void *ctx, const void *data, size_t len,
			      size_t asn1hdrlen)
{
	struct key_preparsed_payload *prep = ctx;
	const void *saved_prep_data;
	size_t saved_prep_datalen;
	int ret;

	saved_prep_data = prep->data;
	saved_prep_datalen = prep->datalen;
	prep->data = data;
	prep->datalen = len;

	ret = user_preparse(prep);

	prep->data = saved_prep_data;
	prep->datalen = saved_prep_datalen;
	return ret;
}