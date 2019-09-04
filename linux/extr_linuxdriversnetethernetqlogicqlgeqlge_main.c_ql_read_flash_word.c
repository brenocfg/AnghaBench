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
struct ql_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  FLASH_ADDR ; 
 int /*<<< orphan*/  FLASH_ADDR_ERR ; 
 int FLASH_ADDR_R ; 
 int /*<<< orphan*/  FLASH_ADDR_RDY ; 
 int /*<<< orphan*/  FLASH_DATA ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int ql_wait_reg_rdy (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ql_read_flash_word(struct ql_adapter *qdev, int offset, __le32 *data)
{
	int status = 0;
	/* wait for reg to come ready */
	status = ql_wait_reg_rdy(qdev,
			FLASH_ADDR, FLASH_ADDR_RDY, FLASH_ADDR_ERR);
	if (status)
		goto exit;
	/* set up for reg read */
	ql_write32(qdev, FLASH_ADDR, FLASH_ADDR_R | offset);
	/* wait for reg to come ready */
	status = ql_wait_reg_rdy(qdev,
			FLASH_ADDR, FLASH_ADDR_RDY, FLASH_ADDR_ERR);
	if (status)
		goto exit;
	 /* This data is stored on flash as an array of
	 * __le32.  Since ql_read32() returns cpu endian
	 * we need to swap it back.
	 */
	*data = cpu_to_le32(ql_read32(qdev, FLASH_DATA));
exit:
	return status;
}