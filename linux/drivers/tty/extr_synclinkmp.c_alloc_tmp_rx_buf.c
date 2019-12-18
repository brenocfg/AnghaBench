#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * tmp_rx_buf; int /*<<< orphan*/  flag_buf; int /*<<< orphan*/  max_frame_size; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_tmp_rx_buf(SLMP_INFO *info)
{
	info->tmp_rx_buf = kmalloc(info->max_frame_size, GFP_KERNEL);
	if (info->tmp_rx_buf == NULL)
		return -ENOMEM;
	/* unused flag buffer to satisfy receive_buf calling interface */
	info->flag_buf = kzalloc(info->max_frame_size, GFP_KERNEL);
	if (!info->flag_buf) {
		kfree(info->tmp_rx_buf);
		info->tmp_rx_buf = NULL;
		return -ENOMEM;
	}
	return 0;
}