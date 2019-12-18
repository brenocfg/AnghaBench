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
struct mousevsc_dev {int init_complete; int /*<<< orphan*/  wait_event; struct hv_device* device; } ;
struct hv_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  hv_set_drvdata (struct hv_device*,struct mousevsc_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct mousevsc_dev* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mousevsc_dev *mousevsc_alloc_device(struct hv_device *device)
{
	struct mousevsc_dev *input_dev;

	input_dev = kzalloc(sizeof(struct mousevsc_dev), GFP_KERNEL);

	if (!input_dev)
		return NULL;

	input_dev->device = device;
	hv_set_drvdata(device, input_dev);
	init_completion(&input_dev->wait_event);
	input_dev->init_complete = false;

	return input_dev;
}