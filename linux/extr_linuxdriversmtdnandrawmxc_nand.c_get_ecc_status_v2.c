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
typedef  int /*<<< orphan*/  u32 ;
struct mxc_nand_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_V1_V2_ECC_STATUS_RESULT ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 get_ecc_status_v2(struct mxc_nand_host *host)
{
	return readl(NFC_V1_V2_ECC_STATUS_RESULT);
}