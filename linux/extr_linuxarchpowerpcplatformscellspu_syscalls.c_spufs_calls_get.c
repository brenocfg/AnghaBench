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
struct spufs_calls {int dummy; } ;

/* Variables and functions */
 struct spufs_calls* spufs_calls ; 

__attribute__((used)) static inline struct spufs_calls *spufs_calls_get(void)
{
	return spufs_calls;
}