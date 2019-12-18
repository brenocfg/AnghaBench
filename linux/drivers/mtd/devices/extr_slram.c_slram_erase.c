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
struct mtd_info {TYPE_1__* priv; } ;
struct erase_info {int /*<<< orphan*/  len; scalar_t__ addr; } ;
struct TYPE_2__ {scalar_t__ start; } ;
typedef  TYPE_1__ slram_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int slram_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	slram_priv_t *priv = mtd->priv;

	memset(priv->start + instr->addr, 0xff, instr->len);

	return(0);
}