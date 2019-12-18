#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {int /*<<< orphan*/  IO_ADDR_R; } ;
struct nand_chip {TYPE_1__ legacy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pasemi_read_buf(struct nand_chip *chip, u_char *buf, int len)
{
	while (len > 0x800) {
		memcpy_fromio(buf, chip->legacy.IO_ADDR_R, 0x800);
		buf += 0x800;
		len -= 0x800;
	}
	memcpy_fromio(buf, chip->legacy.IO_ADDR_R, len);
}