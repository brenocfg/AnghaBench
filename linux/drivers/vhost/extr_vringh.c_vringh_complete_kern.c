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
typedef  int /*<<< orphan*/  u16 ;
struct vringh {int dummy; } ;
struct vring_used_elem {void* len; void* id; } ;

/* Variables and functions */
 int __vringh_complete (struct vringh*,struct vring_used_elem*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_vringh32 (struct vringh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putu16_kern ; 
 int /*<<< orphan*/  putused_kern ; 

int vringh_complete_kern(struct vringh *vrh, u16 head, u32 len)
{
	struct vring_used_elem used;

	used.id = cpu_to_vringh32(vrh, head);
	used.len = cpu_to_vringh32(vrh, len);

	return __vringh_complete(vrh, &used, 1, putu16_kern, putused_kern);
}