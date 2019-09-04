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
struct sm_ftl {scalar_t__ cache_clean; int /*<<< orphan*/  cache_data_invalid_bitmap; scalar_t__ cache_data; } ;

/* Variables and functions */
 int SM_SECTOR_SIZE ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 

__attribute__((used)) static void sm_cache_put(struct sm_ftl *ftl, char *buffer, int boffset)
{
	memcpy(ftl->cache_data + boffset, buffer, SM_SECTOR_SIZE);
	clear_bit(boffset / SM_SECTOR_SIZE, &ftl->cache_data_invalid_bitmap);
	ftl->cache_clean = 0;
}