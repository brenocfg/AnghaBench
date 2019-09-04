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

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* diag204_buf ; 
 int diag204_buf_pages ; 

__attribute__((used)) static void *diag204_alloc_rbuf(void)
{
	diag204_buf = (void*)__get_free_pages(GFP_KERNEL,0);
	if (!diag204_buf)
		return ERR_PTR(-ENOMEM);
	diag204_buf_pages = 1;
	return diag204_buf;
}