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
struct uclogic_drvdata {unsigned int desc_size; int /*<<< orphan*/ * desc_ptr; } ;
struct hid_device {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 struct uclogic_drvdata* hid_get_drvdata (struct hid_device*) ; 

__attribute__((used)) static __u8 *uclogic_report_fixup(struct hid_device *hdev, __u8 *rdesc,
					unsigned int *rsize)
{
	struct uclogic_drvdata *drvdata = hid_get_drvdata(hdev);

	if (drvdata->desc_ptr != NULL) {
		rdesc = drvdata->desc_ptr;
		*rsize = drvdata->desc_size;
	}
	return rdesc;
}