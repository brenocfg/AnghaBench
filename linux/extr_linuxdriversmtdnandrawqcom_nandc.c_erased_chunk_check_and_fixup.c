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
typedef  int u8 ;

/* Variables and functions */
 scalar_t__ memchr_inv (int*,int,int) ; 

__attribute__((used)) static bool erased_chunk_check_and_fixup(u8 *data_buf, int data_len)
{
	u8 empty1, empty2;

	/*
	 * an erased page flags an error in NAND_FLASH_STATUS, check if the page
	 * is erased by looking for 0x54s at offsets 3 and 175 from the
	 * beginning of each codeword
	 */

	empty1 = data_buf[3];
	empty2 = data_buf[175];

	/*
	 * if the erased codework markers, if they exist override them with
	 * 0xffs
	 */
	if ((empty1 == 0x54 && empty2 == 0xff) ||
	    (empty1 == 0xff && empty2 == 0x54)) {
		data_buf[3] = 0xff;
		data_buf[175] = 0xff;
	}

	/*
	 * check if the entire chunk contains 0xffs or not. if it doesn't, then
	 * restore the original values at the special offsets
	 */
	if (memchr_inv(data_buf, 0xff, data_len)) {
		data_buf[3] = empty1;
		data_buf[175] = empty2;

		return false;
	}

	return true;
}