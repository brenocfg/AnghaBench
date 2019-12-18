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
struct TYPE_2__ {int (* set_features ) (struct nand_chip*,int,int /*<<< orphan*/ *) ;} ;
struct nand_chip {TYPE_1__ legacy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int nand_set_features_op (struct nand_chip*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nand_supports_set_features (struct nand_chip*,int) ; 
 int stub1 (struct nand_chip*,int,int /*<<< orphan*/ *) ; 

int nand_set_features(struct nand_chip *chip, int addr,
		      u8 *subfeature_param)
{
	if (!nand_supports_set_features(chip, addr))
		return -ENOTSUPP;

	if (chip->legacy.set_features)
		return chip->legacy.set_features(chip, addr, subfeature_param);

	return nand_set_features_op(chip, addr, subfeature_param);
}