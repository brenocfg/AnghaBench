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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  IO_ADDR_W; } ;
struct nand_chip {TYPE_1__ legacy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite8_rep (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void nand_write_buf(struct nand_chip *chip, const uint8_t *buf, int len)
{
	iowrite8_rep(chip->legacy.IO_ADDR_W, buf, len);
}