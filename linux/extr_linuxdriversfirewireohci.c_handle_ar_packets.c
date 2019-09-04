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
struct ar_context {int dummy; } ;

/* Variables and functions */
 void* handle_ar_packet (struct ar_context*,void*) ; 

__attribute__((used)) static void *handle_ar_packets(struct ar_context *ctx, void *p, void *end)
{
	void *next;

	while (p < end) {
		next = handle_ar_packet(ctx, p);
		if (!next)
			return p;
		p = next;
	}

	return p;
}