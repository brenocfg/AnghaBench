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
struct iio_dev {int dummy; } ;
struct dht11 {size_t num_edges; int /*<<< orphan*/  completion; int /*<<< orphan*/  gpiod; TYPE_1__* edges; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  value; int /*<<< orphan*/  ts; } ;

/* Variables and functions */
 size_t DHT11_EDGES_PER_READ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_get_value (int /*<<< orphan*/ ) ; 
 struct dht11* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  ktime_get_boottime_ns () ; 

__attribute__((used)) static irqreturn_t dht11_handle_irq(int irq, void *data)
{
	struct iio_dev *iio = data;
	struct dht11 *dht11 = iio_priv(iio);

	/* TODO: Consider making the handler safe for IRQ sharing */
	if (dht11->num_edges < DHT11_EDGES_PER_READ && dht11->num_edges >= 0) {
		dht11->edges[dht11->num_edges].ts = ktime_get_boottime_ns();
		dht11->edges[dht11->num_edges++].value =
						gpiod_get_value(dht11->gpiod);

		if (dht11->num_edges >= DHT11_EDGES_PER_READ)
			complete(&dht11->completion);
	}

	return IRQ_HANDLED;
}