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
struct mtk_ecc {TYPE_1__* caps; } ;
struct TYPE_2__ {unsigned int parity_bits; } ;

/* Variables and functions */

unsigned int mtk_ecc_get_parity_bits(struct mtk_ecc *ecc)
{
	return ecc->caps->parity_bits;
}