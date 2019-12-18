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
struct input_dev {int /*<<< orphan*/  evbit; } ;
struct iforce {TYPE_1__* xport_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* start_io ) (struct iforce*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EV_FF ; 
 int /*<<< orphan*/  FF_CMD_ENABLE ; 
 int /*<<< orphan*/  iforce_send_packet (struct iforce*,int /*<<< orphan*/ ,char*) ; 
 struct iforce* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  stub1 (struct iforce*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iforce_open(struct input_dev *dev)
{
	struct iforce *iforce = input_get_drvdata(dev);

	iforce->xport_ops->start_io(iforce);

	if (test_bit(EV_FF, dev->evbit)) {
		/* Enable force feedback */
		iforce_send_packet(iforce, FF_CMD_ENABLE, "\004");
	}

	return 0;
}