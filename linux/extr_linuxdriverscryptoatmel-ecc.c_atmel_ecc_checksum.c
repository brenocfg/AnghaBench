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
struct atmel_ecc_cmd {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRC_SIZE ; 
 int /*<<< orphan*/  atmel_ecc_crc16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void atmel_ecc_checksum(struct atmel_ecc_cmd *cmd)
{
	u8 *data = &cmd->count;
	size_t len = cmd->count - CRC_SIZE;
	u16 *crc16 = (u16 *)(data + len);

	*crc16 = atmel_ecc_crc16(0, data, len);
}