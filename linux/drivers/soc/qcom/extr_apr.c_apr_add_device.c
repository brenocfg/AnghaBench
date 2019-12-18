#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct apr_device_id {scalar_t__ svc_id; int /*<<< orphan*/  domain_id; int /*<<< orphan*/  name; int /*<<< orphan*/  svc_version; } ;
struct TYPE_5__ {int /*<<< orphan*/ * driver; int /*<<< orphan*/  release; struct device_node* of_node; struct device* parent; int /*<<< orphan*/ * bus; } ;
struct apr_device {TYPE_1__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/  version; int /*<<< orphan*/  domain_id; scalar_t__ svc_id; int /*<<< orphan*/  lock; } ;
struct apr {int /*<<< orphan*/  svcs_lock; int /*<<< orphan*/  svcs_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_NAME_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  apr_dev_release ; 
 int /*<<< orphan*/  aprbus ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct apr* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  idr_alloc (int /*<<< orphan*/ *,struct apr_device*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct apr_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct device_node*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apr_add_device(struct device *dev, struct device_node *np,
			  const struct apr_device_id *id)
{
	struct apr *apr = dev_get_drvdata(dev);
	struct apr_device *adev = NULL;
	int ret;

	adev = kzalloc(sizeof(*adev), GFP_KERNEL);
	if (!adev)
		return -ENOMEM;

	spin_lock_init(&adev->lock);

	adev->svc_id = id->svc_id;
	adev->domain_id = id->domain_id;
	adev->version = id->svc_version;
	if (np)
		snprintf(adev->name, APR_NAME_SIZE, "%pOFn", np);
	else
		strscpy(adev->name, id->name, APR_NAME_SIZE);

	dev_set_name(&adev->dev, "aprsvc:%s:%x:%x", adev->name,
		     id->domain_id, id->svc_id);

	adev->dev.bus = &aprbus;
	adev->dev.parent = dev;
	adev->dev.of_node = np;
	adev->dev.release = apr_dev_release;
	adev->dev.driver = NULL;

	spin_lock(&apr->svcs_lock);
	idr_alloc(&apr->svcs_idr, adev, id->svc_id,
		  id->svc_id + 1, GFP_ATOMIC);
	spin_unlock(&apr->svcs_lock);

	dev_info(dev, "Adding APR dev: %s\n", dev_name(&adev->dev));

	ret = device_register(&adev->dev);
	if (ret) {
		dev_err(dev, "device_register failed: %d\n", ret);
		put_device(&adev->dev);
	}

	return ret;
}