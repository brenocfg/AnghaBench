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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  CRC32C (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b ; 
 int /*<<< orphan*/  get_unaligned_le16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  h ; 
 int /*<<< orphan*/  w ; 

__attribute__((used)) static u32 crc32c_mips_le_hw(u32 crc_, const u8 *p, unsigned int len)
{
	u32 crc = crc_;

#ifdef CONFIG_64BIT
	while (len >= sizeof(u64)) {
		u64 value = get_unaligned_le64(p);

		CRC32C(crc, value, d);
		p += sizeof(u64);
		len -= sizeof(u64);
	}

	if (len & sizeof(u32)) {
#else /* !CONFIG_64BIT */
	while (len >= sizeof(u32)) {
#endif
		u32 value = get_unaligned_le32(p);

		CRC32C(crc, value, w);
		p += sizeof(u32);
		len -= sizeof(u32);
	}

	if (len & sizeof(u16)) {
		u16 value = get_unaligned_le16(p);

		CRC32C(crc, value, h);
		p += sizeof(u16);
	}

	if (len & sizeof(u8)) {
		u8 value = *p++;

		CRC32C(crc, value, b);
	}
	return crc;
}