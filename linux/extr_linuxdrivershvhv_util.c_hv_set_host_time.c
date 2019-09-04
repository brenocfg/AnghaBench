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
struct work_struct {int dummy; } ;
struct timespec64 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_settimeofday64 (struct timespec64*) ; 
 struct timespec64 hv_get_adj_host_time () ; 

__attribute__((used)) static void hv_set_host_time(struct work_struct *work)
{
	struct timespec64 ts = hv_get_adj_host_time();

	do_settimeofday64(&ts);
}