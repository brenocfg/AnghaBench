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
struct nicvf {scalar_t__ rb_pageref; int /*<<< orphan*/  rb_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  page_ref_add (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void nicvf_get_page(struct nicvf *nic)
{
	if (!nic->rb_pageref || !nic->rb_page)
		return;

	page_ref_add(nic->rb_page, nic->rb_pageref);
	nic->rb_pageref = 0;
}