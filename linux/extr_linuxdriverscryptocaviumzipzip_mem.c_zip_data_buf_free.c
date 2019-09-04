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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zip_dbg (char*,int /*<<< orphan*/ *) ; 

void zip_data_buf_free(u8 *ptr, u64 size)
{
	zip_dbg("Freeing data buffer 0x%lx\n", ptr);

	free_pages((u64)ptr, get_order(size));
}