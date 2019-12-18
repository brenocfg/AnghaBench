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
typedef  int u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int IF_COMM_WR ; 
 int /*<<< orphan*/  c_can_obj_update (struct net_device*,int,int,int) ; 

__attribute__((used)) static inline void c_can_object_put(struct net_device *dev, int iface,
				    u32 obj, u32 cmd)
{
	c_can_obj_update(dev, iface, cmd | IF_COMM_WR, obj);
}