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
struct s3c_rtc {TYPE_1__* data; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* irq_handler ) (struct s3c_rtc*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  S3C2410_INTP_ALM ; 
 int /*<<< orphan*/  stub1 (struct s3c_rtc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t s3c_rtc_alarmirq(int irq, void *id)
{
	struct s3c_rtc *info = (struct s3c_rtc *)id;

	if (info->data->irq_handler)
		info->data->irq_handler(info, S3C2410_INTP_ALM);

	return IRQ_HANDLED;
}