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
struct xen_front_pgdir_shbuf {scalar_t__ num_pages; scalar_t__ num_grefs; } ;

/* Variables and functions */
 scalar_t__ get_num_pages_dir (struct xen_front_pgdir_shbuf*) ; 

__attribute__((used)) static void guest_calc_num_grefs(struct xen_front_pgdir_shbuf *buf)
{
	/*
	 * Number of pages the page directory consumes itself
	 * plus grefs for the buffer pages.
	 */
	buf->num_grefs = get_num_pages_dir(buf) + buf->num_pages;
}