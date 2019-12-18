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
struct file {int dummy; } ;

/* Variables and functions */
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hp_sdc_rtc_async_queue ; 

__attribute__((used)) static int hp_sdc_rtc_fasync (int fd, struct file *filp, int on)
{
        return fasync_helper (fd, filp, on, &hp_sdc_rtc_async_queue);
}