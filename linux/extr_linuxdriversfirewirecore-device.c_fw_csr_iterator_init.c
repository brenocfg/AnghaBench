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
typedef  int u32 ;
struct fw_csr_iterator {int const* p; int const* end; } ;

/* Variables and functions */

void fw_csr_iterator_init(struct fw_csr_iterator *ci, const u32 *p)
{
	ci->p = p + 1;
	ci->end = ci->p + (p[0] >> 16);
}