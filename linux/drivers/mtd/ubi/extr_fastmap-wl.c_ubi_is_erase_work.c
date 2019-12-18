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
struct ubi_work {scalar_t__ func; } ;

/* Variables and functions */
 scalar_t__ erase_worker ; 

int ubi_is_erase_work(struct ubi_work *wrk)
{
	return wrk->func == erase_worker;
}