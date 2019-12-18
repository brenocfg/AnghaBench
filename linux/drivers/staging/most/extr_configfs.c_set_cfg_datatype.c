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
struct mdev_link {int /*<<< orphan*/  datatype; int /*<<< orphan*/  channel; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int most_set_cfg_datatype (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_cfg_datatype(struct mdev_link *link)
{
	return most_set_cfg_datatype(link->device, link->channel,
				     link->datatype);
}