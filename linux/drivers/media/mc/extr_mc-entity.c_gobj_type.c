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
typedef  enum media_gobj_type { ____Placeholder_media_gobj_type } media_gobj_type ;

/* Variables and functions */
#define  MEDIA_GRAPH_ENTITY 131 
#define  MEDIA_GRAPH_INTF_DEVNODE 130 
#define  MEDIA_GRAPH_LINK 129 
#define  MEDIA_GRAPH_PAD 128 

__attribute__((used)) static inline const char *gobj_type(enum media_gobj_type type)
{
	switch (type) {
	case MEDIA_GRAPH_ENTITY:
		return "entity";
	case MEDIA_GRAPH_PAD:
		return "pad";
	case MEDIA_GRAPH_LINK:
		return "link";
	case MEDIA_GRAPH_INTF_DEVNODE:
		return "intf-devnode";
	default:
		return "unknown";
	}
}