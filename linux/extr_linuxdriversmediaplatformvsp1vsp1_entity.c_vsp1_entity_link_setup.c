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
typedef  int /*<<< orphan*/  u32 ;
struct media_pad {int flags; } ;
struct media_entity {int dummy; } ;

/* Variables and functions */
 int MEDIA_PAD_FL_SOURCE ; 
 int vsp1_entity_link_setup_sink (struct media_pad const*,struct media_pad const*,int /*<<< orphan*/ ) ; 
 int vsp1_entity_link_setup_source (struct media_pad const*,struct media_pad const*,int /*<<< orphan*/ ) ; 

int vsp1_entity_link_setup(struct media_entity *entity,
			   const struct media_pad *local,
			   const struct media_pad *remote, u32 flags)
{
	if (local->flags & MEDIA_PAD_FL_SOURCE)
		return vsp1_entity_link_setup_source(local, remote, flags);
	else
		return vsp1_entity_link_setup_sink(remote, local, flags);
}