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
struct sge_fl {unsigned int size; } ;

/* Variables and functions */
 unsigned int FL_PER_EQ_UNIT ; 

__attribute__((used)) static inline unsigned int fl_cap(const struct sge_fl *fl)
{
	return fl->size - FL_PER_EQ_UNIT;
}