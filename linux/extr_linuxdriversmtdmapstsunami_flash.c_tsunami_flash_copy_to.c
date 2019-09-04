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
 int /*<<< orphan*/  tsunami_tig_writeb (unsigned char const,unsigned long) ; 

__attribute__((used)) static void tsunami_flash_copy_to(
	struct map_info *map, unsigned long offset,
	const void *addr, ssize_t len)
{
	const unsigned char *src;
	src = addr;
	while(len && (offset < MAX_TIG_FLASH_SIZE)) {
		tsunami_tig_writeb(*src, offset);
		offset++;
		src++;
		len--;
	}
}