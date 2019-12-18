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
struct mvs_info {void* tags; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_bit (unsigned int,void*) ; 

void mvs_tag_set(struct mvs_info *mvi, unsigned int tag)
{
	void *bitmap = mvi->tags;
	set_bit(tag, bitmap);
}