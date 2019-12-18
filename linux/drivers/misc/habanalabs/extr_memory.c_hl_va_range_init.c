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
typedef  int u64 ;
struct hl_va_range {int start_addr; int end_addr; int /*<<< orphan*/  list; } ;
struct hl_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 int add_va_block (struct hl_device*,struct hl_va_range*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int hl_va_range_init(struct hl_device *hdev,
		struct hl_va_range *va_range, u64 start, u64 end)
{
	int rc;

	INIT_LIST_HEAD(&va_range->list);

	/* PAGE_SIZE alignment */

	if (start & (PAGE_SIZE - 1)) {
		start &= PAGE_MASK;
		start += PAGE_SIZE;
	}

	if (end & (PAGE_SIZE - 1))
		end &= PAGE_MASK;

	if (start >= end) {
		dev_err(hdev->dev, "too small vm range for va list\n");
		return -EFAULT;
	}

	rc = add_va_block(hdev, va_range, start, end);

	if (rc) {
		dev_err(hdev->dev, "Failed to init host va list\n");
		return rc;
	}

	va_range->start_addr = start;
	va_range->end_addr = end;

	return 0;
}