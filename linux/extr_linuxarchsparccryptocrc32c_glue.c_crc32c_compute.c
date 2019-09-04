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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  __crc32c_le (int /*<<< orphan*/ ,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  crc32c_sparc64 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void crc32c_compute(u32 *crcp, const u64 *data, unsigned int len)
{
	unsigned int asm_len;

	asm_len = len & ~7U;
	if (asm_len) {
		crc32c_sparc64(crcp, data, asm_len);
		data += asm_len / 8;
		len -= asm_len;
	}
	if (len)
		*crcp = __crc32c_le(*crcp, (const unsigned char *) data, len);
}