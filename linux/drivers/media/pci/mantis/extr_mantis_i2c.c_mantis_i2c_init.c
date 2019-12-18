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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct i2c_adapter {int timeout; int retries; TYPE_1__ dev; int /*<<< orphan*/ * algo_data; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct mantis_pci {int i2c_rc; int /*<<< orphan*/  i2c_lock; int /*<<< orphan*/  i2c_wq; struct pci_dev* pdev; struct i2c_adapter adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  MANTIS_INT_I2CDONE ; 
 int /*<<< orphan*/  MANTIS_INT_MASK ; 
 int /*<<< orphan*/  MANTIS_INT_STAT ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int i2c_add_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct mantis_pci*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mantis_algo ; 
 int /*<<< orphan*/  mantis_mask_ints (struct mantis_pci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

int mantis_i2c_init(struct mantis_pci *mantis)
{
	u32 intstat;
	struct i2c_adapter *i2c_adapter = &mantis->adapter;
	struct pci_dev *pdev		= mantis->pdev;

	init_waitqueue_head(&mantis->i2c_wq);
	mutex_init(&mantis->i2c_lock);
	strscpy(i2c_adapter->name, "Mantis I2C", sizeof(i2c_adapter->name));
	i2c_set_adapdata(i2c_adapter, mantis);

	i2c_adapter->owner	= THIS_MODULE;
	i2c_adapter->algo	= &mantis_algo;
	i2c_adapter->algo_data	= NULL;
	i2c_adapter->timeout	= 500;
	i2c_adapter->retries	= 3;
	i2c_adapter->dev.parent	= &pdev->dev;

	mantis->i2c_rc		= i2c_add_adapter(i2c_adapter);
	if (mantis->i2c_rc < 0)
		return mantis->i2c_rc;

	dprintk(MANTIS_DEBUG, 1, "Initializing I2C ..");

	intstat = mmread(MANTIS_INT_STAT);
	mmread(MANTIS_INT_MASK);
	mmwrite(intstat, MANTIS_INT_STAT);
	dprintk(MANTIS_DEBUG, 1, "Disabling I2C interrupt");
	mantis_mask_ints(mantis, MANTIS_INT_I2CDONE);

	return 0;
}