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
struct resource {int flags; int start; } ;
struct intel_th_drvdata {int dummy; } ;
struct intel_th {int id; int major; unsigned int num_resources; int irq; struct resource* resource; struct intel_th_drvdata* drvdata; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct intel_th* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IORESOURCE_IRQ ; 
 int /*<<< orphan*/  TH_POSSIBLE_OUTPUTS ; 
 int __register_chrdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct intel_th*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  intel_th_free (struct intel_th*) ; 
 int /*<<< orphan*/  intel_th_ida ; 
 int /*<<< orphan*/  intel_th_output_fops ; 
 int intel_th_populate (struct intel_th*) ; 
 int /*<<< orphan*/  kfree (struct intel_th*) ; 
 struct intel_th* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_allow (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_no_callbacks (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 

struct intel_th *
intel_th_alloc(struct device *dev, struct intel_th_drvdata *drvdata,
	       struct resource *devres, unsigned int ndevres, int irq)
{
	struct intel_th *th;
	int err, r;

	if (irq == -1)
		for (r = 0; r < ndevres; r++)
			if (devres[r].flags & IORESOURCE_IRQ) {
				irq = devres[r].start;
				break;
			}

	th = kzalloc(sizeof(*th), GFP_KERNEL);
	if (!th)
		return ERR_PTR(-ENOMEM);

	th->id = ida_simple_get(&intel_th_ida, 0, 0, GFP_KERNEL);
	if (th->id < 0) {
		err = th->id;
		goto err_alloc;
	}

	th->major = __register_chrdev(0, 0, TH_POSSIBLE_OUTPUTS,
				      "intel_th/output", &intel_th_output_fops);
	if (th->major < 0) {
		err = th->major;
		goto err_ida;
	}
	th->dev = dev;
	th->drvdata = drvdata;

	th->resource = devres;
	th->num_resources = ndevres;
	th->irq = irq;

	dev_set_drvdata(dev, th);

	pm_runtime_no_callbacks(dev);
	pm_runtime_put(dev);
	pm_runtime_allow(dev);

	err = intel_th_populate(th);
	if (err) {
		/* free the subdevices and undo everything */
		intel_th_free(th);
		return ERR_PTR(err);
	}

	return th;

err_ida:
	ida_simple_remove(&intel_th_ida, th->id);

err_alloc:
	kfree(th);

	return ERR_PTR(err);
}