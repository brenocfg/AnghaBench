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
struct TYPE_2__ {int /*<<< orphan*/  set_feature_list; scalar_t__ supports_set_get_features; } ;
struct nand_chip {TYPE_1__ parameters; } ;

/* Variables and functions */
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nand_supports_set_features(struct nand_chip *chip, int addr)
{
	return (chip->parameters.supports_set_get_features &&
		test_bit(addr, chip->parameters.set_feature_list));
}