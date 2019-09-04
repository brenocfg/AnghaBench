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
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 unsigned char* s3c_get_bufferram (struct mtd_info*,int) ; 

__attribute__((used)) static int onenand_write_bufferram(struct mtd_info *mtd, int area,
				   const unsigned char *buffer, int offset,
				   size_t count)
{
	unsigned char *p;

	p = s3c_get_bufferram(mtd, area);
	memcpy(p + offset, buffer, count);
	return 0;
}