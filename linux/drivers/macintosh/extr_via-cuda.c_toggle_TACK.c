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
 size_t B ; 
 int TACK ; 
 int in_8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * via ; 

__attribute__((used)) static inline void toggle_TACK(void)
{
	out_8(&via[B], in_8(&via[B]) ^ TACK);
}