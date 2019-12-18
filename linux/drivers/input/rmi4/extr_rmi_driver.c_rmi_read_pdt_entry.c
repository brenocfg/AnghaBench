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
typedef  int u8 ;
typedef  int u16 ;
struct rmi_device {int /*<<< orphan*/  dev; } ;
struct pdt_entry {int page_start; int query_base_addr; int command_base_addr; int control_base_addr; int data_base_addr; int interrupt_source_count; int function_version; int function_number; } ;

/* Variables and functions */
 int RMI4_PAGE_MASK ; 
 int RMI_PDT_ENTRY_SIZE ; 
 int RMI_PDT_FUNCTION_VERSION_MASK ; 
 int RMI_PDT_INT_SOURCE_COUNT_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int rmi_read_block (struct rmi_device*,int,int*,int) ; 

__attribute__((used)) static int rmi_read_pdt_entry(struct rmi_device *rmi_dev,
			      struct pdt_entry *entry, u16 pdt_address)
{
	u8 buf[RMI_PDT_ENTRY_SIZE];
	int error;

	error = rmi_read_block(rmi_dev, pdt_address, buf, RMI_PDT_ENTRY_SIZE);
	if (error) {
		dev_err(&rmi_dev->dev, "Read PDT entry at %#06x failed, code: %d.\n",
				pdt_address, error);
		return error;
	}

	entry->page_start = pdt_address & RMI4_PAGE_MASK;
	entry->query_base_addr = buf[0];
	entry->command_base_addr = buf[1];
	entry->control_base_addr = buf[2];
	entry->data_base_addr = buf[3];
	entry->interrupt_source_count = buf[4] & RMI_PDT_INT_SOURCE_COUNT_MASK;
	entry->function_version = (buf[4] & RMI_PDT_FUNCTION_VERSION_MASK) >> 5;
	entry->function_number = buf[5];

	return 0;
}