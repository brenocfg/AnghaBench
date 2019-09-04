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
typedef  unsigned long long u64 ;
typedef  unsigned long long u32 ;
struct ib_field {int size_bits; int offset_bits; int struct_offset_bytes; int offset_words; scalar_t__ struct_size_bytes; int /*<<< orphan*/  field_name; } ;
typedef  int __be64 ;
typedef  int __be32 ;

/* Variables and functions */
 int cpu_to_be32 (unsigned long long) ; 
 int cpu_to_be64 (unsigned long long) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int value_read (int,scalar_t__,void*) ; 

void ib_pack(const struct ib_field        *desc,
	     int                           desc_len,
	     void                         *structure,
	     void                         *buf)
{
	int i;

	for (i = 0; i < desc_len; ++i) {
		if (desc[i].size_bits <= 32) {
			int shift;
			u32 val;
			__be32 mask;
			__be32 *addr;

			shift = 32 - desc[i].offset_bits - desc[i].size_bits;
			if (desc[i].struct_size_bytes)
				val = value_read(desc[i].struct_offset_bytes,
						 desc[i].struct_size_bytes,
						 structure) << shift;
			else
				val = 0;

			mask = cpu_to_be32(((1ull << desc[i].size_bits) - 1) << shift);
			addr = (__be32 *) buf + desc[i].offset_words;
			*addr = (*addr & ~mask) | (cpu_to_be32(val) & mask);
		} else if (desc[i].size_bits <= 64) {
			int shift;
			u64 val;
			__be64 mask;
			__be64 *addr;

			shift = 64 - desc[i].offset_bits - desc[i].size_bits;
			if (desc[i].struct_size_bytes)
				val = value_read(desc[i].struct_offset_bytes,
						 desc[i].struct_size_bytes,
						 structure) << shift;
			else
				val = 0;

			mask = cpu_to_be64((~0ull >> (64 - desc[i].size_bits)) << shift);
			addr = (__be64 *) ((__be32 *) buf + desc[i].offset_words);
			*addr = (*addr & ~mask) | (cpu_to_be64(val) & mask);
		} else {
			if (desc[i].offset_bits % 8 ||
			    desc[i].size_bits   % 8) {
				pr_warn("Structure field %s of size %d bits is not byte-aligned\n",
					desc[i].field_name, desc[i].size_bits);
			}

			if (desc[i].struct_size_bytes)
				memcpy(buf + desc[i].offset_words * 4 +
				       desc[i].offset_bits / 8,
				       structure + desc[i].struct_offset_bytes,
				       desc[i].size_bits / 8);
			else
				memset(buf + desc[i].offset_words * 4 +
				       desc[i].offset_bits / 8,
				       0,
				       desc[i].size_bits / 8);
		}
	}
}