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
struct nand_chip {int dummy; } ;
struct nand_bbt_descr {int dummy; } ;

/* Variables and functions */
 int create_bbt (struct nand_chip*,int /*<<< orphan*/ *,struct nand_bbt_descr*,int) ; 
 int /*<<< orphan*/ * nand_get_data_buf (struct nand_chip*) ; 

__attribute__((used)) static inline int nand_memory_bbt(struct nand_chip *this,
				  struct nand_bbt_descr *bd)
{
	u8 *pagebuf = nand_get_data_buf(this);

	return create_bbt(this, pagebuf, bd, -1);
}