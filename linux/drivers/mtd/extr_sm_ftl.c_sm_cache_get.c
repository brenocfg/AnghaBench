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
struct sm_ftl {scalar_t__ cache_data; int /*<<< orphan*/  cache_data_invalid_bitmap; } ;

/* Variables and functions */
 int SM_SECTOR_SIZE ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,int) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sm_cache_get(struct sm_ftl *ftl, char *buffer, int boffset)
{
	if (test_bit(boffset / SM_SECTOR_SIZE,
		&ftl->cache_data_invalid_bitmap))
			return -1;

	memcpy(buffer, ftl->cache_data + boffset, SM_SECTOR_SIZE);
	return 0;
}