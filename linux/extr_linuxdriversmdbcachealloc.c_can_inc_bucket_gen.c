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
struct bucket {int dummy; } ;

/* Variables and functions */
 scalar_t__ BUCKET_GC_GEN_MAX ; 
 scalar_t__ bucket_gc_gen (struct bucket*) ; 

__attribute__((used)) static inline bool can_inc_bucket_gen(struct bucket *b)
{
	return bucket_gc_gen(b) < BUCKET_GC_GEN_MAX;
}