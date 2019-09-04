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
typedef  unsigned int u32 ;
struct rbd_image_header {unsigned int obj_order; } ;

/* Variables and functions */

__attribute__((used)) static u32 rbd_obj_bytes(struct rbd_image_header *header)
{
	return 1U << header->obj_order;
}