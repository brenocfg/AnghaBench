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
typedef  int u16 ;
struct esas2r_adapter {int /*<<< orphan*/  flash_ver; } ;
typedef  int /*<<< orphan*/  bytes ;

/* Variables and functions */
 int FBT_CPYR ; 
 int FBT_FLASH_VER ; 
 int FBT_SETUP ; 
 scalar_t__ FLS_OFFSET_CPYR ; 
 int esas2r_print_flash_rev (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_read_flash_block (struct esas2r_adapter*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int le16_to_cpu (int) ; 
 int /*<<< orphan*/  le32_to_cpu (int) ; 

bool esas2r_read_flash_rev(struct esas2r_adapter *a)
{
	u8 bytes[256];
	u16 *pw;
	u16 *pwstart;
	u16 type;
	u16 size;
	u32 sz;

	sz = sizeof(bytes);
	pw = (u16 *)(bytes + sz);
	pwstart = (u16 *)bytes + 2;

	if (!esas2r_read_flash_block(a, bytes, FLS_OFFSET_CPYR - sz, sz))
		goto invalid_rev;

	while (pw >= pwstart) {
		pw--;
		type = le16_to_cpu(*pw);
		pw--;
		size = le16_to_cpu(*pw);
		pw -= size / 2;

		if (type == FBT_CPYR
		    || type == FBT_SETUP
		    || pw < pwstart)
			continue;

		if (type == FBT_FLASH_VER)
			a->flash_ver = le32_to_cpu(*(u32 *)pw);

		break;
	}

invalid_rev:
	return esas2r_print_flash_rev(a);
}