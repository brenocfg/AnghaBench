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
typedef  int /*<<< orphan*/  uint16_t ;
struct mxc_nand_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_V1_V2_CONFIG1 ; 
 int /*<<< orphan*/  NFC_V1_V2_CONFIG1_INT_MSK ; 
 int /*<<< orphan*/  readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void irq_control_v1_v2(struct mxc_nand_host *host, int activate)
{
	uint16_t tmp;

	tmp = readw(NFC_V1_V2_CONFIG1);

	if (activate)
		tmp &= ~NFC_V1_V2_CONFIG1_INT_MSK;
	else
		tmp |= NFC_V1_V2_CONFIG1_INT_MSK;

	writew(tmp, NFC_V1_V2_CONFIG1);
}