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
struct intel_th {int id; int major; int irq; int num_resources; struct resource* resource; struct intel_th_drvdata* drvdata; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct intel_th* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  IORESOURCE_IRQ 129 
#define  IORESOURCE_MEM 128 
 int IORESOURCE_TYPE_BITS ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  TH_POSSIBLE_OUTPUTS ; 
 int __register_chrdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __unregister_chrdev (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct intel_th*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct intel_th*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  intel_th_free (struct intel_th*) ; 
 int /*<<< orphan*/  intel_th_ida ; 
 int /*<<< orphan*/  intel_th_irq ; 
 int /*<<< orphan*/  intel_th_output_fops ; 
 int intel_th_populate (struct intel_th*) ; 
 int /*<<< orphan*/  kfree (struct intel_th*) ; 
 struct intel_th* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_allow (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_no_callbacks (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 

struct intel_th *
intel_th_alloc(struct device *dev, struct intel_th_drvdata *drvdata,
	       struct resource *devres, unsigned int ndevres)
{
	int err, r, nr_mmios = 0;
	struct intel_th *th;

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
	th->irq = -1;
	th->dev = dev;
	th->drvdata = drvdata;

	for (r = 0; r < ndevres; r++)
		switch (devres[r].flags & IORESOURCE_TYPE_BITS) {
		case IORESOURCE_MEM:
			th->resource[nr_mmios++] = devres[r];
			break;
		case IORESOURCE_IRQ:
			err = devm_request_irq(dev, devres[r].start,
					       intel_th_irq, IRQF_SHARED,
					       dev_name(dev), th);
			if (err)
				goto err_chrdev;

			if (th->irq == -1)
				th->irq = devres[r].start;
			break;
		default:
			dev_warn(dev, "Unknown resource type %lx\n",
				 devres[r].flags);
			break;
		}

	th->num_resources = nr_mmios;

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

err_chrdev:
	__unregister_chrdev(th->major, 0, TH_POSSIBLE_OUTPUTS,
			    "intel_th/output");

err_ida:
	ida_simple_remove(&intel_th_ida, th->id);

err_alloc:
	kfree(th);

	return ERR_PTR(err);
}