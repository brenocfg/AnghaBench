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
typedef  int uint16_t ;
struct mxc_nand_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_STATUS ; 
 int /*<<< orphan*/  NFC_V3_CONFIG1 ; 
 int /*<<< orphan*/  NFC_V3_LAUNCH ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_op_done (struct mxc_nand_host*,int) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t get_dev_status_v3(struct mxc_nand_host *host)
{
	writew(NFC_STATUS, NFC_V3_LAUNCH);
	wait_op_done(host, true);

	return readl(NFC_V3_CONFIG1) >> 16;
}