#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct media_link {TYPE_2__* source; TYPE_1__* sink; } ;
struct media_entity {int dummy; } ;
struct TYPE_4__ {struct media_entity* entity; } ;
struct TYPE_3__ {struct media_entity* entity; } ;

/* Variables and functions */

__attribute__((used)) static struct media_entity *
media_entity_other(struct media_entity *entity, struct media_link *link)
{
	if (link->source->entity == entity)
		return link->sink->entity;
	else
		return link->source->entity;
}