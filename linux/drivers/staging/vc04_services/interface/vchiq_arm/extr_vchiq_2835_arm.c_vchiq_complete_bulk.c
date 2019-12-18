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
struct vchiq_pagelist_info {int dummy; } ;
struct vchiq_bulk {scalar_t__ actual; scalar_t__ remote_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pagelist (struct vchiq_pagelist_info*,scalar_t__) ; 

void
vchiq_complete_bulk(struct vchiq_bulk *bulk)
{
	if (bulk && bulk->remote_data && bulk->actual)
		free_pagelist((struct vchiq_pagelist_info *)bulk->remote_data,
			      bulk->actual);
}