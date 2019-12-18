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
struct vmballoon {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 unsigned long atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmballoon_deflate (struct vmballoon*,unsigned long,int) ; 

__attribute__((used)) static void vmballoon_pop(struct vmballoon *b)
{
	unsigned long size;

	while ((size = atomic64_read(&b->size)))
		vmballoon_deflate(b, size, false);
}