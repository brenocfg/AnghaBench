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
struct qcom_nand_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_nand_cw_read (struct qcom_nand_controller*,int) ; 
 int /*<<< orphan*/  config_nand_page_read (struct qcom_nand_controller*) ; 

__attribute__((used)) static void
config_nand_single_cw_page_read(struct qcom_nand_controller *nandc,
				bool use_ecc)
{
	config_nand_page_read(nandc);
	config_nand_cw_read(nandc, use_ecc);
}