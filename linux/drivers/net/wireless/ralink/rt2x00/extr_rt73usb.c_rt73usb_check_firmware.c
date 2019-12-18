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
typedef  int u16 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int FW_BAD_CRC ; 
 int FW_BAD_LENGTH ; 
 int FW_OK ; 
 int crc_itu_t (int /*<<< orphan*/ ,int const*,size_t const) ; 
 int crc_itu_t_byte (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt73usb_check_firmware(struct rt2x00_dev *rt2x00dev,
				  const u8 *data, const size_t len)
{
	u16 fw_crc;
	u16 crc;

	/*
	 * Only support 2kb firmware files.
	 */
	if (len != 2048)
		return FW_BAD_LENGTH;

	/*
	 * The last 2 bytes in the firmware array are the crc checksum itself,
	 * this means that we should never pass those 2 bytes to the crc
	 * algorithm.
	 */
	fw_crc = (data[len - 2] << 8 | data[len - 1]);

	/*
	 * Use the crc itu-t algorithm.
	 */
	crc = crc_itu_t(0, data, len - 2);
	crc = crc_itu_t_byte(crc, 0);
	crc = crc_itu_t_byte(crc, 0);

	return (fw_crc == crc) ? FW_OK : FW_BAD_CRC;
}