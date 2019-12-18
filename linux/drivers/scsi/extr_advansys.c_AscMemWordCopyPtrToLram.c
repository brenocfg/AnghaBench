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
typedef  int ushort ;
typedef  int uchar ;
typedef  scalar_t__ PortAddr ;

/* Variables and functions */
 int /*<<< orphan*/  AscSetChipLramAddr (scalar_t__,int) ; 
 scalar_t__ IOP_RAM_DATA ; 
 int /*<<< orphan*/  outpw (scalar_t__,int) ; 

__attribute__((used)) static void
AscMemWordCopyPtrToLram(PortAddr iop_base, ushort s_addr,
			const uchar *s_buffer, int words)
{
	int i;

	AscSetChipLramAddr(iop_base, s_addr);
	for (i = 0; i < 2 * words; i += 2) {
		/*
		 * On a little-endian system the second argument below
		 * produces a little-endian ushort which is written to
		 * LRAM in little-endian order. On a big-endian system
		 * the second argument produces a big-endian ushort which
		 * is "transparently" byte-swapped by outpw() and written
		 * in little-endian order to LRAM.
		 */
		outpw(iop_base + IOP_RAM_DATA,
		      ((ushort)s_buffer[i + 1] << 8) | s_buffer[i]);
	}
}