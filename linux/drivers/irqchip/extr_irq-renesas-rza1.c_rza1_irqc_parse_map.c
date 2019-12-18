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
typedef  unsigned int u32 ;
struct rza1_irqc_priv {TYPE_1__* map; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {unsigned int args_count; unsigned int* args; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQC_NUM_IRQ ; 
 unsigned int be32_to_cpup (int /*<<< orphan*/  const*) ; 
 struct device_node* of_find_node_by_phandle (unsigned int) ; 
 int /*<<< orphan*/ * of_get_property (int /*<<< orphan*/ ,char*,unsigned int*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 unsigned int of_property_read_u32 (struct device_node*,char*,unsigned int*) ; 

__attribute__((used)) static int rza1_irqc_parse_map(struct rza1_irqc_priv *priv,
			       struct device_node *gic_node)
{
	unsigned int imaplen, i, j, ret;
	struct device *dev = priv->dev;
	struct device_node *ipar;
	const __be32 *imap;
	u32 intsize;

	imap = of_get_property(dev->of_node, "interrupt-map", &imaplen);
	if (!imap)
		return -EINVAL;

	for (i = 0; i < IRQC_NUM_IRQ; i++) {
		if (imaplen < 3)
			return -EINVAL;

		/* Check interrupt number, ignore sense */
		if (be32_to_cpup(imap) != i)
			return -EINVAL;

		ipar = of_find_node_by_phandle(be32_to_cpup(imap + 2));
		if (ipar != gic_node) {
			of_node_put(ipar);
			return -EINVAL;
		}

		imap += 3;
		imaplen -= 3;

		ret = of_property_read_u32(ipar, "#interrupt-cells", &intsize);
		of_node_put(ipar);
		if (ret)
			return ret;

		if (imaplen < intsize)
			return -EINVAL;

		priv->map[i].args_count = intsize;
		for (j = 0; j < intsize; j++)
			priv->map[i].args[j] = be32_to_cpup(imap++);

		imaplen -= intsize;
	}

	return 0;
}