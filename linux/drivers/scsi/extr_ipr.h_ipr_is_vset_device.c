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
struct ipr_resource_entry {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ IPR_RES_TYPE_VOLUME_SET ; 

__attribute__((used)) static inline int ipr_is_vset_device(struct ipr_resource_entry *res)
{
	return res->type == IPR_RES_TYPE_VOLUME_SET;
}