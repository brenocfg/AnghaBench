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
struct rcar_du_device {TYPE_1__* info; } ;
struct TYPE_2__ {unsigned int quirks; } ;

/* Variables and functions */

__attribute__((used)) static inline bool rcar_du_needs(struct rcar_du_device *rcdu,
				 unsigned int quirk)
{
	return rcdu->info->quirks & quirk;
}