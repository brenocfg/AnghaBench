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
struct dasd_information2_t {unsigned int label_block; int FBA_layout; int characteristics_size; scalar_t__ confdata_size; int /*<<< orphan*/  characteristics; int /*<<< orphan*/  format; } ;
struct dasd_diag_private {int /*<<< orphan*/  rdc_data; scalar_t__ pt_block; } ;
struct dasd_device {struct dasd_diag_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_FORMAT_LDL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
dasd_diag_fill_info(struct dasd_device * device,
		    struct dasd_information2_t * info)
{
	struct dasd_diag_private *private = device->private;

	info->label_block = (unsigned int) private->pt_block;
	info->FBA_layout = 1;
	info->format = DASD_FORMAT_LDL;
	info->characteristics_size = sizeof(private->rdc_data);
	memcpy(info->characteristics, &private->rdc_data,
	       sizeof(private->rdc_data));
	info->confdata_size = 0;
	return 0;
}