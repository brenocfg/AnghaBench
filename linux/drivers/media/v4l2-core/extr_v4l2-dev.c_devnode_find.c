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
struct video_device {int /*<<< orphan*/  vfl_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  devnode_bits (int /*<<< orphan*/ ) ; 
 int find_next_zero_bit (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline int devnode_find(struct video_device *vdev, int from, int to)
{
	return find_next_zero_bit(devnode_bits(vdev->vfl_type), to, from);
}