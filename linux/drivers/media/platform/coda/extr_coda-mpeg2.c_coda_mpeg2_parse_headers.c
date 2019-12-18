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
typedef  int u8 ;
typedef  int u32 ;
struct coda_ctx {int dummy; } ;
struct TYPE_2__ {int member_0; int member_1; int member_2; int member_3; } ;

/* Variables and functions */
 scalar_t__ memcmp (int*,int const*,int) ; 

u32 coda_mpeg2_parse_headers(struct coda_ctx *ctx, u8 *buf, u32 size)
{
	static const u8 sequence_header_start[4] = { 0x00, 0x00, 0x01, 0xb3 };
	static const union {
		u8 extension_start[4];
		u8 start_code_prefix[3];
	} u = { { 0x00, 0x00, 0x01, 0xb5 } };

	if (size < 22 ||
	    memcmp(buf, sequence_header_start, 4) != 0)
		return 0;

	if ((size == 22 ||
	     (size >= 25 && memcmp(buf + 22, u.start_code_prefix, 3) == 0)) &&
	    memcmp(buf + 12, u.extension_start, 4) == 0)
		return 22;

	if ((size == 86 ||
	     (size > 89 && memcmp(buf + 86, u.start_code_prefix, 3) == 0)) &&
	    memcmp(buf + 76, u.extension_start, 4) == 0)
		return 86;

	return 0;
}