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
struct map_info {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 unsigned long MAX_TIG_FLASH_SIZE ; 
 unsigned char tsunami_tig_readb (unsigned long) ; 

__attribute__((used)) static void tsunami_flash_copy_from(
	struct map_info *map, void *addr, unsigned long offset, ssize_t len)
{
	unsigned char *dest;
	dest = addr;
	while(len && (offset < MAX_TIG_FLASH_SIZE)) {
		*dest = tsunami_tig_readb(offset);
		offset++;
		dest++;
		len--;
	}
}