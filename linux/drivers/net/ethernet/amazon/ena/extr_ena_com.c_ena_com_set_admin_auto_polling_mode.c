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
struct TYPE_2__ {int auto_polling; } ;
struct ena_com_dev {TYPE_1__ admin_queue; } ;

/* Variables and functions */

void ena_com_set_admin_auto_polling_mode(struct ena_com_dev *ena_dev,
					 bool polling)
{
	ena_dev->admin_queue.auto_polling = polling;
}