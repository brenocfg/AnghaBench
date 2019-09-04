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
struct TYPE_2__ {void* os_context; } ;
typedef  TYPE_1__ divas_um_idi_entity_t ;

/* Variables and functions */

void *diva_um_id_get_os_context(void *entity)
{
	return (((divas_um_idi_entity_t *) entity)->os_context);
}