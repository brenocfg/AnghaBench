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
typedef  scalar_t__ u8 ;
struct nand_manufacturer {scalar_t__ id; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct nand_manufacturer const*) ; 
 struct nand_manufacturer const* nand_manufacturers ; 

const struct nand_manufacturer *nand_get_manufacturer(u8 id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(nand_manufacturers); i++)
		if (nand_manufacturers[i].id == id)
			return &nand_manufacturers[i];

	return NULL;
}