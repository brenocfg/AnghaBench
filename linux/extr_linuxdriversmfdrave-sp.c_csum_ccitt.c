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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  crc_ccitt_false (int,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void csum_ccitt(const u8 *buf, size_t size, u8 *crc)
{
	const u16 calculated = crc_ccitt_false(0xffff, buf, size);

	/*
	 * While the rest of the wire protocol is little-endian,
	 * CCITT-16 CRC in RDU2 device is sent out in big-endian order.
	 */
	put_unaligned_be16(calculated, crc);
}