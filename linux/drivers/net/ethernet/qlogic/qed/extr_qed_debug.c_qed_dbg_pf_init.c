#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct qed_dev {TYPE_1__* firmware; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  qed_dbg_set_bin_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_dbg_user_set_bin_ptr (int /*<<< orphan*/ *) ; 

void qed_dbg_pf_init(struct qed_dev *cdev)
{
	const u8 *dbg_values;

	/* Debug values are after init values.
	 * The offset is the first dword of the file.
	 */
	dbg_values = cdev->firmware->data + *(u32 *)cdev->firmware->data;
	qed_dbg_set_bin_ptr((u8 *)dbg_values);
	qed_dbg_user_set_bin_ptr((u8 *)dbg_values);
}