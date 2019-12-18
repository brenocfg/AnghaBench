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
struct tun_page {int /*<<< orphan*/  count; scalar_t__ page; } ;

/* Variables and functions */
 int /*<<< orphan*/  __page_frag_cache_drain (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tun_put_page(struct tun_page *tpage)
{
	if (tpage->page)
		__page_frag_cache_drain(tpage->page, tpage->count);
}