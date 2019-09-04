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
struct dsaf_device {TYPE_1__** rcb_common; } ;
struct TYPE_2__ {int max_q_per_vf; } ;

/* Variables and functions */

__attribute__((used)) static int hns_ae_get_q_num_per_vf(
	struct dsaf_device *dsaf_dev, int port)
{
	return dsaf_dev->rcb_common[0]->max_q_per_vf;
}