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
typedef  int u8 ;
typedef  enum mlx5_dev_event { ____Placeholder_mlx5_dev_event } mlx5_dev_event ;

/* Variables and functions */
 int MLX5_DEV_EVENT_CLIENT_REREG ; 
 int MLX5_DEV_EVENT_GUID_CHANGE ; 
 int MLX5_DEV_EVENT_LID_CHANGE ; 
 int MLX5_DEV_EVENT_PKEY_CHANGE ; 
 int MLX5_DEV_EVENT_PORT_DOWN ; 
 int MLX5_DEV_EVENT_PORT_INITIALIZED ; 
 int MLX5_DEV_EVENT_PORT_UP ; 
#define  MLX5_PORT_CHANGE_SUBTYPE_ACTIVE 134 
#define  MLX5_PORT_CHANGE_SUBTYPE_CLIENT_REREG 133 
#define  MLX5_PORT_CHANGE_SUBTYPE_DOWN 132 
#define  MLX5_PORT_CHANGE_SUBTYPE_GUID 131 
#define  MLX5_PORT_CHANGE_SUBTYPE_INITIALIZED 130 
#define  MLX5_PORT_CHANGE_SUBTYPE_LID 129 
#define  MLX5_PORT_CHANGE_SUBTYPE_PKEY 128 

__attribute__((used)) static enum mlx5_dev_event port_subtype_event(u8 subtype)
{
	switch (subtype) {
	case MLX5_PORT_CHANGE_SUBTYPE_DOWN:
		return MLX5_DEV_EVENT_PORT_DOWN;
	case MLX5_PORT_CHANGE_SUBTYPE_ACTIVE:
		return MLX5_DEV_EVENT_PORT_UP;
	case MLX5_PORT_CHANGE_SUBTYPE_INITIALIZED:
		return MLX5_DEV_EVENT_PORT_INITIALIZED;
	case MLX5_PORT_CHANGE_SUBTYPE_LID:
		return MLX5_DEV_EVENT_LID_CHANGE;
	case MLX5_PORT_CHANGE_SUBTYPE_PKEY:
		return MLX5_DEV_EVENT_PKEY_CHANGE;
	case MLX5_PORT_CHANGE_SUBTYPE_GUID:
		return MLX5_DEV_EVENT_GUID_CHANGE;
	case MLX5_PORT_CHANGE_SUBTYPE_CLIENT_REREG:
		return MLX5_DEV_EVENT_CLIENT_REREG;
	}
	return -1;
}