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
struct mutex {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 

__attribute__((used)) static inline void ksz_regmap_unlock(void *__mtx)
{
	struct mutex *mtx = __mtx;
	mutex_unlock(mtx);
}