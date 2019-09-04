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
typedef  scalar_t__ u8 ;
struct opal_dev {int /*<<< orphan*/  parsed; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ OPAL_MANUFACTURED_INACTIVE ; 
 int parse_and_check_status (struct opal_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ response_get_u64 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int get_lsp_lifecycle_cont(struct opal_dev *dev)
{
	u8 lc_status;
	int error = 0;

	error = parse_and_check_status(dev);
	if (error)
		return error;

	lc_status = response_get_u64(&dev->parsed, 4);
	/* 0x08 is Manufacured Inactive */
	/* 0x09 is Manufactured */
	if (lc_status != OPAL_MANUFACTURED_INACTIVE) {
		pr_debug("Couldn't determine the status of the Lifecycle state\n");
		return -ENODEV;
	}

	return 0;
}