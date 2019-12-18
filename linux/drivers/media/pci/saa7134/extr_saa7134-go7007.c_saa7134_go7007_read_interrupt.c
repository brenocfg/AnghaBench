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
struct saa7134_go7007 {struct saa7134_dev* dev; } ;
struct saa7134_dev {int dummy; } ;
struct go7007 {int interrupt_available; int /*<<< orphan*/  interrupt_data; int /*<<< orphan*/  interrupt_value; struct saa7134_go7007* hpi_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ADDR_INTR_RET_DATA ; 
 int /*<<< orphan*/  HPI_ADDR_INTR_RET_VALUE ; 
 int /*<<< orphan*/  gpio_read (struct saa7134_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int saa7134_go7007_read_interrupt(struct go7007 *go)
{
	struct saa7134_go7007 *saa = go->hpi_context;
	struct saa7134_dev *dev = saa->dev;

	/* XXX we need to wait if there is no interrupt available */
	go->interrupt_available = 1;
	gpio_read(dev, HPI_ADDR_INTR_RET_VALUE, &go->interrupt_value);
	gpio_read(dev, HPI_ADDR_INTR_RET_DATA, &go->interrupt_data);
#ifdef GO7007_HPI_DEBUG
	pr_debug("saa7134-go7007: ReadInterrupt: %04x %04x\n",
			go->interrupt_value, go->interrupt_data);
#endif
	return 0;
}