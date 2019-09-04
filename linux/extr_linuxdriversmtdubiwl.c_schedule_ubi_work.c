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
struct ubi_work {int dummy; } ;
struct ubi_device {int /*<<< orphan*/  work_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  __schedule_ubi_work (struct ubi_device*,struct ubi_work*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void schedule_ubi_work(struct ubi_device *ubi, struct ubi_work *wrk)
{
	down_read(&ubi->work_sem);
	__schedule_ubi_work(ubi, wrk);
	up_read(&ubi->work_sem);
}