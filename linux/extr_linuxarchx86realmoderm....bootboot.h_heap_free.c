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

/* Variables and functions */
 scalar_t__ HEAP ; 
 scalar_t__ heap_end ; 

__attribute__((used)) static inline bool heap_free(size_t n)
{
	return (int)(heap_end-HEAP) >= (int)n;
}