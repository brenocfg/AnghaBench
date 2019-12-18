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
typedef  scalar_t__ u32 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_EEP_ADDR_CMD ; 
 int /*<<< orphan*/  ASIC_EEP_DATA ; 
 int /*<<< orphan*/  CMD_NOP ; 
 int /*<<< orphan*/  CMD_READ_DATA (scalar_t__) ; 
 int EP_PAGE_DWORDS ; 
 scalar_t__ read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_page(struct hfi1_devdata *dd, u32 offset, u32 *result)
{
	int i;

	write_csr(dd, ASIC_EEP_ADDR_CMD, CMD_READ_DATA(offset));
	for (i = 0; i < EP_PAGE_DWORDS; i++)
		result[i] = (u32)read_csr(dd, ASIC_EEP_DATA);
	write_csr(dd, ASIC_EEP_ADDR_CMD, CMD_NOP); /* close open page */
}