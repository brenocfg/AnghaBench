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
struct ehea_top_bmap {scalar_t__* dir; } ;
struct ehea_dir_bmap {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ehea_init_top_bmap(struct ehea_top_bmap *ehea_top_bmap,
				     int dir)
{
	if (!ehea_top_bmap->dir[dir]) {
		ehea_top_bmap->dir[dir] =
			kzalloc(sizeof(struct ehea_dir_bmap), GFP_KERNEL);
		if (!ehea_top_bmap->dir[dir])
			return -ENOMEM;
	}
	return 0;
}