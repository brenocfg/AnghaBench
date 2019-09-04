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
typedef  scalar_t__ uint8_t ;
struct bucket {scalar_t__ last_gc; scalar_t__ gen; } ;

/* Variables and functions */

__attribute__((used)) static inline uint8_t bucket_gc_gen(struct bucket *b)
{
	return b->gen - b->last_gc;
}