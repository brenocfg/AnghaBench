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
struct mxc_nand_host {int /*<<< orphan*/ * devtype_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  imx21_nand_devtype_data ; 

__attribute__((used)) static inline int is_imx21_nfc(struct mxc_nand_host *host)
{
	return host->devtype_data == &imx21_nand_devtype_data;
}