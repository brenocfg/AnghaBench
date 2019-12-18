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
struct device {int /*<<< orphan*/ * type; int /*<<< orphan*/ * bus; } ;
struct pci_epf {struct device dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct pci_epf* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dev_set_name (struct device*,char*,char const*) ; 
 int device_add (struct device*) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 int /*<<< orphan*/  kfree (struct pci_epf*) ; 
 int /*<<< orphan*/  kstrndup (char const*,int,int /*<<< orphan*/ ) ; 
 struct pci_epf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_epf_bus_type ; 
 int /*<<< orphan*/  pci_epf_type ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 char const* strchrnul (char const*,char) ; 

struct pci_epf *pci_epf_create(const char *name)
{
	int ret;
	struct pci_epf *epf;
	struct device *dev;
	int len;

	epf = kzalloc(sizeof(*epf), GFP_KERNEL);
	if (!epf)
		return ERR_PTR(-ENOMEM);

	len = strchrnul(name, '.') - name;
	epf->name = kstrndup(name, len, GFP_KERNEL);
	if (!epf->name) {
		kfree(epf);
		return ERR_PTR(-ENOMEM);
	}

	dev = &epf->dev;
	device_initialize(dev);
	dev->bus = &pci_epf_bus_type;
	dev->type = &pci_epf_type;

	ret = dev_set_name(dev, "%s", name);
	if (ret) {
		put_device(dev);
		return ERR_PTR(ret);
	}

	ret = device_add(dev);
	if (ret) {
		put_device(dev);
		return ERR_PTR(ret);
	}

	return epf;
}