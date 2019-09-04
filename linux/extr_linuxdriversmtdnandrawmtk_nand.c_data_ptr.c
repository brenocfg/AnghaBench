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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int size; } ;
struct nand_chip {TYPE_1__ ecc; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 *data_ptr(struct nand_chip *chip, const u8 *p, int i)
{
	return (u8 *)p + i * chip->ecc.size;
}