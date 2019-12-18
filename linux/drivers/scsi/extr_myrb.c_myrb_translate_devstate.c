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
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  memmove (void*,void*,int) ; 

__attribute__((used)) static inline void myrb_translate_devstate(void *state)
{
	memcpy(state + 2, state + 3, 1);
	memmove(state + 4, state + 5, 2);
	memmove(state + 6, state + 8, 4);
}