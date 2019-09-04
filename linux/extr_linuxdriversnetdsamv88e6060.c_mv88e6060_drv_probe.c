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
struct mv88e6060_priv {int sw_addr; struct mii_bus* bus; } ;
struct mii_bus {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mv88e6060_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct mii_bus* dsa_host_dev_to_mii_bus (struct device*) ; 
 char* mv88e6060_get_name (struct mii_bus*,int) ; 

__attribute__((used)) static const char *mv88e6060_drv_probe(struct device *dsa_dev,
				       struct device *host_dev, int sw_addr,
				       void **_priv)
{
	struct mii_bus *bus = dsa_host_dev_to_mii_bus(host_dev);
	struct mv88e6060_priv *priv;
	const char *name;

	name = mv88e6060_get_name(bus, sw_addr);
	if (name) {
		priv = devm_kzalloc(dsa_dev, sizeof(*priv), GFP_KERNEL);
		if (!priv)
			return NULL;
		*_priv = priv;
		priv->bus = bus;
		priv->sw_addr = sw_addr;
	}

	return name;
}