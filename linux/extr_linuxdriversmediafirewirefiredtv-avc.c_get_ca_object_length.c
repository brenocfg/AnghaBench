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
struct avc_response_frame {int* operand; } ;

/* Variables and functions */

__attribute__((used)) static int get_ca_object_length(struct avc_response_frame *r)
{
#if 0 /* FIXME: unused */
	int size = 0;
	int i;

	if (r->operand[7] & 0x80)
		for (i = 0; i < (r->operand[7] & 0x7f); i++) {
			size <<= 8;
			size += r->operand[8 + i];
		}
#endif
	return r->operand[7];
}