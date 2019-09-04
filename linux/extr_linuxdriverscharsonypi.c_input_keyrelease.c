#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct sonypi_keypress {int /*<<< orphan*/  dev; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  kp ;
struct TYPE_2__ {int /*<<< orphan*/  input_fifo_lock; int /*<<< orphan*/  input_fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int kfifo_out_locked (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_1__ sonypi_device ; 

__attribute__((used)) static void input_keyrelease(struct work_struct *work)
{
	struct sonypi_keypress kp;

	while (kfifo_out_locked(&sonypi_device.input_fifo, (unsigned char *)&kp,
			 sizeof(kp), &sonypi_device.input_fifo_lock)
			== sizeof(kp)) {
		msleep(10);
		input_report_key(kp.dev, kp.key, 0);
		input_sync(kp.dev);
	}
}