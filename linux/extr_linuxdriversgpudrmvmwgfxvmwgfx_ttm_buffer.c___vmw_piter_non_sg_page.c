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
struct vmw_piter {size_t i; struct page** pages; } ;
struct page {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct page *__vmw_piter_non_sg_page(struct vmw_piter *viter)
{
	return viter->pages[viter->i];
}