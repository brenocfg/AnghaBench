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
struct a6xx_gpu_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 void* state_kcalloc (struct a6xx_gpu_state*,int,size_t) ; 

void *state_kmemdup(struct a6xx_gpu_state *a6xx_state, void *src,
		size_t size)
{
	void *dst = state_kcalloc(a6xx_state, 1, size);

	if (dst)
		memcpy(dst, src, size);
	return dst;
}