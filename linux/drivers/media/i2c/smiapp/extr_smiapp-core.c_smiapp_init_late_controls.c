#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct smiapp_sensor {unsigned long* valid_link_freqs; size_t compressed_min_bpp; TYPE_4__* src; TYPE_3__* hwcfg; int /*<<< orphan*/  link_freq; TYPE_2__* pixel_array; int /*<<< orphan*/ * test_data; TYPE_1__* csi_format; } ;
struct TYPE_10__ {int error; } ;
struct TYPE_9__ {TYPE_5__ ctrl_handler; } ;
struct TYPE_8__ {int /*<<< orphan*/  op_sys_clock; } ;
struct TYPE_7__ {int /*<<< orphan*/  ctrl_handler; } ;
struct TYPE_6__ {size_t compressed; int width; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V4L2_CID_LINK_FREQ ; 
 scalar_t__ V4L2_CID_TEST_PATTERN_RED ; 
 int /*<<< orphan*/  __ffs (unsigned long) ; 
 int /*<<< orphan*/  __fls (unsigned long) ; 
 int /*<<< orphan*/  smiapp_ctrl_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_new_int_menu (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int smiapp_init_late_controls(struct smiapp_sensor *sensor)
{
	unsigned long *valid_link_freqs = &sensor->valid_link_freqs[
		sensor->csi_format->compressed - sensor->compressed_min_bpp];
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(sensor->test_data); i++) {
		int max_value = (1 << sensor->csi_format->width) - 1;

		sensor->test_data[i] = v4l2_ctrl_new_std(
				&sensor->pixel_array->ctrl_handler,
				&smiapp_ctrl_ops, V4L2_CID_TEST_PATTERN_RED + i,
				0, max_value, 1, max_value);
	}

	sensor->link_freq = v4l2_ctrl_new_int_menu(
		&sensor->src->ctrl_handler, &smiapp_ctrl_ops,
		V4L2_CID_LINK_FREQ, __fls(*valid_link_freqs),
		__ffs(*valid_link_freqs), sensor->hwcfg->op_sys_clock);

	return sensor->src->ctrl_handler.error;
}