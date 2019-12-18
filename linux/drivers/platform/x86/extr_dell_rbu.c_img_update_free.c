#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int image_update_ordernum; scalar_t__ bios_image_size; scalar_t__ image_update_buffer_size; int /*<<< orphan*/ * image_update_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__ rbu_data ; 

__attribute__((used)) static void img_update_free(void)
{
	if (!rbu_data.image_update_buffer)
		return;
	/*
	 * zero out this buffer before freeing it to get rid of any stale
	 * BIOS image copied in memory.
	 */
	memset(rbu_data.image_update_buffer, 0,
		rbu_data.image_update_buffer_size);
	free_pages((unsigned long) rbu_data.image_update_buffer,
		rbu_data.image_update_ordernum);

	/*
	 * Re-initialize the rbu_data variables after a free
	 */
	rbu_data.image_update_ordernum = -1;
	rbu_data.image_update_buffer = NULL;
	rbu_data.image_update_buffer_size = 0;
	rbu_data.bios_image_size = 0;
}