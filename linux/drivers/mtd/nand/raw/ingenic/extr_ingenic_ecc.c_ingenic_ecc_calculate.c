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
struct ingenic_ecc_params {int dummy; } ;
struct ingenic_ecc {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* calculate ) (struct ingenic_ecc*,struct ingenic_ecc_params*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (struct ingenic_ecc*,struct ingenic_ecc_params*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int ingenic_ecc_calculate(struct ingenic_ecc *ecc,
			  struct ingenic_ecc_params *params,
			  const u8 *buf, u8 *ecc_code)
{
	return ecc->ops->calculate(ecc, params, buf, ecc_code);
}