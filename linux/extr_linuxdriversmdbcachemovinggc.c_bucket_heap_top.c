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
struct cache {int /*<<< orphan*/  heap; } ;
struct bucket {int dummy; } ;

/* Variables and functions */
 unsigned int GC_SECTORS_USED (struct bucket*) ; 
 struct bucket* heap_peek (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int bucket_heap_top(struct cache *ca)
{
	struct bucket *b;

	return (b = heap_peek(&ca->heap)) ? GC_SECTORS_USED(b) : 0;
}