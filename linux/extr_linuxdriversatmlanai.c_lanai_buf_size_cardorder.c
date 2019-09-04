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
struct lanai_buffer {int dummy; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lanai_buf_size (struct lanai_buffer const*) ; 

__attribute__((used)) static int lanai_buf_size_cardorder(const struct lanai_buffer *buf)
{
	int order = get_order(lanai_buf_size(buf)) + (PAGE_SHIFT - 10);

	/* This can only happen if PAGE_SIZE is gigantic, but just in case */
	if (order > 7)
		order = 7;
	return order;
}