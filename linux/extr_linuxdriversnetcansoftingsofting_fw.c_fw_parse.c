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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int EINVAL ; 
 int le16_to_cpup (void*) ; 
 int /*<<< orphan*/  le32_to_cpup (void*) ; 

__attribute__((used)) static int fw_parse(const uint8_t **pmem, uint16_t *ptype, uint32_t *paddr,
		uint16_t *plen, const uint8_t **pdat)
{
	uint16_t checksum[2];
	const uint8_t *mem;
	const uint8_t *end;

	/*
	 * firmware records are a binary, unaligned stream composed of:
	 * uint16_t type;
	 * uint32_t addr;
	 * uint16_t len;
	 * uint8_t dat[len];
	 * uint16_t checksum;
	 * all values in little endian.
	 * We could define a struct for this, with __attribute__((packed)),
	 * but would that solve the alignment in _all_ cases (cfr. the
	 * struct itself may be an odd address)?
	 *
	 * I chose to use leXX_to_cpup() since this solves both
	 * endianness & alignment.
	 */
	mem = *pmem;
	*ptype = le16_to_cpup((void *)&mem[0]);
	*paddr = le32_to_cpup((void *)&mem[2]);
	*plen = le16_to_cpup((void *)&mem[6]);
	*pdat = &mem[8];
	/* verify checksum */
	end = &mem[8 + *plen];
	checksum[0] = le16_to_cpup((void *)end);
	for (checksum[1] = 0; mem < end; ++mem)
		checksum[1] += *mem;
	if (checksum[0] != checksum[1])
		return -EINVAL;
	/* increment */
	*pmem += 10 + *plen;
	return 0;
}