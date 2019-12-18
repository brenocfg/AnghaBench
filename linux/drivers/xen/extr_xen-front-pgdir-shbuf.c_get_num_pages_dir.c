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
struct xen_front_pgdir_shbuf {int /*<<< orphan*/  num_pages; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEN_NUM_GREFS_PER_PAGE ; 

__attribute__((used)) static int get_num_pages_dir(struct xen_front_pgdir_shbuf *buf)
{
	return DIV_ROUND_UP(buf->num_pages, XEN_NUM_GREFS_PER_PAGE);
}