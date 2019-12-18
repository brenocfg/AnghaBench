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
struct ehea_top_bmap {int dummy; } ;
struct ehea_bmap {scalar_t__* top; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ehea_init_top_bmap (scalar_t__,int) ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ehea_init_bmap(struct ehea_bmap *ehea_bmap, int top, int dir)
{
	if (!ehea_bmap->top[top]) {
		ehea_bmap->top[top] =
			kzalloc(sizeof(struct ehea_top_bmap), GFP_KERNEL);
		if (!ehea_bmap->top[top])
			return -ENOMEM;
	}
	return ehea_init_top_bmap(ehea_bmap->top[top], dir);
}