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
struct ingenic_ecc_params {int dummy; } ;
struct ingenic_ecc {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 

int ingenic_ecc_correct(struct ingenic_ecc *ecc,
			struct ingenic_ecc_params *params, u8 *buf,
			u8 *ecc_code)
{
	return -ENODEV;
}