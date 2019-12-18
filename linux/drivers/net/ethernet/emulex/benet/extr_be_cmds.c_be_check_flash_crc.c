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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct be_adapter {int dummy; } ;

/* Variables and functions */
 int be_cmd_get_flash_crc (struct be_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int be_check_flash_crc(struct be_adapter *adapter, const u8 *p,
			      u32 img_offset, u32 img_size, int hdr_size,
			      u16 img_optype, bool *crc_match)
{
	u32 crc_offset;
	int status;
	u8 crc[4];

	status = be_cmd_get_flash_crc(adapter, crc, img_optype, img_offset,
				      img_size - 4);
	if (status)
		return status;

	crc_offset = hdr_size + img_offset + img_size - 4;

	/* Skip flashing, if crc of flashed region matches */
	if (!memcmp(crc, p + crc_offset, 4))
		*crc_match = true;
	else
		*crc_match = false;

	return status;
}