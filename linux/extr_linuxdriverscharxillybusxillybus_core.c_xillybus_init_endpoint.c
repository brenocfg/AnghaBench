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
struct xilly_endpoint_hardware {int dummy; } ;
struct xilly_endpoint {int msg_counter; int /*<<< orphan*/  register_mutex; int /*<<< orphan*/  ep_wait; scalar_t__ fatal_error; scalar_t__ failed_messages; struct xilly_endpoint_hardware* ephw; struct device* dev; struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct xilly_endpoint* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct xilly_endpoint *xillybus_init_endpoint(struct pci_dev *pdev,
					      struct device *dev,
					      struct xilly_endpoint_hardware
					      *ephw)
{
	struct xilly_endpoint *endpoint;

	endpoint = devm_kzalloc(dev, sizeof(*endpoint), GFP_KERNEL);
	if (!endpoint)
		return NULL;

	endpoint->pdev = pdev;
	endpoint->dev = dev;
	endpoint->ephw = ephw;
	endpoint->msg_counter = 0x0b;
	endpoint->failed_messages = 0;
	endpoint->fatal_error = 0;

	init_waitqueue_head(&endpoint->ep_wait);
	mutex_init(&endpoint->register_mutex);

	return endpoint;
}