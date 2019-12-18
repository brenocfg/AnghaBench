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
struct ksz_device {void* priv; struct dsa_switch* ds; struct device* dev; } ;
struct dsa_switch {struct ksz_device* priv; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_MAX_PORTS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ksz_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct dsa_switch* dsa_switch_alloc (struct device*,int /*<<< orphan*/ ) ; 

struct ksz_device *ksz_switch_alloc(struct device *base, void *priv)
{
	struct dsa_switch *ds;
	struct ksz_device *swdev;

	ds = dsa_switch_alloc(base, DSA_MAX_PORTS);
	if (!ds)
		return NULL;

	swdev = devm_kzalloc(base, sizeof(*swdev), GFP_KERNEL);
	if (!swdev)
		return NULL;

	ds->priv = swdev;
	swdev->dev = base;

	swdev->ds = ds;
	swdev->priv = priv;

	return swdev;
}