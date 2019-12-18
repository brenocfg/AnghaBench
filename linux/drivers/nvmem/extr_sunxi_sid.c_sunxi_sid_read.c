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
struct sunxi_sid {scalar_t__ value_offset; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy_fromio (void*,scalar_t__,size_t) ; 

__attribute__((used)) static int sunxi_sid_read(void *context, unsigned int offset,
			  void *val, size_t bytes)
{
	struct sunxi_sid *sid = context;

	memcpy_fromio(val, sid->base + sid->value_offset + offset, bytes);

	return 0;
}