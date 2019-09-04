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
typedef  int /*<<< orphan*/  u64 ;
struct rb_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_to_hole_size (struct rb_node*) ; 

__attribute__((used)) static u64 rb_to_hole_size_or_zero(struct rb_node *rb)
{
	return rb ? rb_to_hole_size(rb) : 0;
}