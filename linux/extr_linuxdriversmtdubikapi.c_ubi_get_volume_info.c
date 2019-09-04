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
struct ubi_volume_info {int dummy; } ;
struct ubi_volume_desc {TYPE_1__* vol; } ;
struct TYPE_2__ {int /*<<< orphan*/  ubi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ubi_do_get_volume_info (int /*<<< orphan*/ ,TYPE_1__*,struct ubi_volume_info*) ; 

void ubi_get_volume_info(struct ubi_volume_desc *desc,
			 struct ubi_volume_info *vi)
{
	ubi_do_get_volume_info(desc->vol->ubi, desc->vol, vi);
}