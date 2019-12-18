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
struct lis3lv02d {int /*<<< orphan*/ * data_ready_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  lis3lv02d_get_xyz (struct lis3lv02d*,int*,int*,int*) ; 

__attribute__((used)) static inline void lis302dl_data_ready(struct lis3lv02d *lis3, int index)
{
	int dummy;

	/* Dummy read to ack interrupt */
	lis3lv02d_get_xyz(lis3, &dummy, &dummy, &dummy);
	lis3->data_ready_count[index]++;
}