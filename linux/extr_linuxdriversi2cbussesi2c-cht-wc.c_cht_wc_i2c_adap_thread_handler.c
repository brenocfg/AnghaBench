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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct cht_wc_i2c_adap {int irq_mask; int read_data; int io_error; int done; int /*<<< orphan*/  client_irq; int /*<<< orphan*/  wait; int /*<<< orphan*/  adap_lock; TYPE_1__ adapter; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHT_WC_EXTCHGRIRQ ; 
 int CHT_WC_EXTCHGRIRQ_ADAP_IRQMASK ; 
 int CHT_WC_EXTCHGRIRQ_CLIENT_IRQ ; 
 int CHT_WC_EXTCHGRIRQ_NACK_IRQ ; 
 int /*<<< orphan*/  CHT_WC_I2C_RDDATA ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t cht_wc_i2c_adap_thread_handler(int id, void *data)
{
	struct cht_wc_i2c_adap *adap = data;
	int ret, reg;

	mutex_lock(&adap->adap_lock);

	/* Read IRQs */
	ret = regmap_read(adap->regmap, CHT_WC_EXTCHGRIRQ, &reg);
	if (ret) {
		dev_err(&adap->adapter.dev, "Error reading extchgrirq reg\n");
		mutex_unlock(&adap->adap_lock);
		return IRQ_NONE;
	}

	reg &= ~adap->irq_mask;

	/* Reads must be acked after reading the received data. */
	ret = regmap_read(adap->regmap, CHT_WC_I2C_RDDATA, &adap->read_data);
	if (ret)
		adap->io_error = true;

	/*
	 * Immediately ack IRQs, so that if new IRQs arrives while we're
	 * handling the previous ones our irq will re-trigger when we're done.
	 */
	ret = regmap_write(adap->regmap, CHT_WC_EXTCHGRIRQ, reg);
	if (ret)
		dev_err(&adap->adapter.dev, "Error writing extchgrirq reg\n");

	if (reg & CHT_WC_EXTCHGRIRQ_ADAP_IRQMASK) {
		adap->io_error |= !!(reg & CHT_WC_EXTCHGRIRQ_NACK_IRQ);
		adap->done = true;
	}

	mutex_unlock(&adap->adap_lock);

	if (reg & CHT_WC_EXTCHGRIRQ_ADAP_IRQMASK)
		wake_up(&adap->wait);

	/*
	 * Do NOT use handle_nested_irq here, the client irq handler will
	 * likely want to do i2c transfers and the i2c controller uses this
	 * interrupt handler as well, so running the client irq handler from
	 * this thread will cause things to lock up.
	 */
	if (reg & CHT_WC_EXTCHGRIRQ_CLIENT_IRQ) {
		/*
		 * generic_handle_irq expects local IRQs to be disabled
		 * as normally it is called from interrupt context.
		 */
		local_irq_disable();
		generic_handle_irq(adap->client_irq);
		local_irq_enable();
	}

	return IRQ_HANDLED;
}