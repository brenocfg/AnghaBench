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
typedef  int /*<<< orphan*/  u32 ;
struct pblk {int dummy; } ;
struct line_header {int dummy; } ;
typedef  int /*<<< orphan*/  crc ;

/* Variables and functions */
 int /*<<< orphan*/  crc32_le (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static inline u32 pblk_calc_meta_header_crc(struct pblk *pblk,
					    struct line_header *header)
{
	u32 crc = ~(u32)0;

	crc = crc32_le(crc, (unsigned char *)header + sizeof(crc),
				sizeof(struct line_header) - sizeof(crc));

	return crc;
}