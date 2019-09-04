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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct dc_bios {scalar_t__ bios_size; int /*<<< orphan*/ * bios; } ;

/* Variables and functions */

uint8_t *bios_get_image(struct dc_bios *bp,
	uint32_t offset,
	uint32_t size)
{
	if (bp->bios && offset + size < bp->bios_size)
		return bp->bios + offset;
	else
		return NULL;
}