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
struct request_queue {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int queue_max_hw_sectors (struct request_queue*) ; 
 int /*<<< orphan*/  queue_var_show (int,char*) ; 

__attribute__((used)) static ssize_t queue_max_hw_sectors_show(struct request_queue *q, char *page)
{
	int max_hw_sectors_kb = queue_max_hw_sectors(q) >> 1;

	return queue_var_show(max_hw_sectors_kb, (page));
}