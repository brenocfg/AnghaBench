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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct hvc_struct {int /*<<< orphan*/  flags; } ;
struct hvc_opal_priv {int /*<<< orphan*/  hvsi; scalar_t__ proto; } ;
struct hv_ops {int dummy; } ;
typedef  scalar_t__ hv_protocol_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HV_PROTOCOL_HVSI ; 
 scalar_t__ HV_PROTOCOL_RAW ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (struct hvc_struct*) ; 
 int /*<<< orphan*/  MAX_VIO_PUT_CHARS ; 
 int /*<<< orphan*/  OPAL_EVENT_CONSOLE_INPUT ; 
 int PTR_ERR (struct hvc_struct*) ; 
 unsigned int be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct hvc_struct*) ; 
 struct hvc_struct* hvc_alloc (unsigned int,unsigned int,struct hv_ops const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hvc_instantiate (unsigned int,unsigned int,struct hv_ops const*) ; 
 struct hvc_opal_priv hvc_opal_boot_priv ; 
 struct hv_ops hvc_opal_hvsi_ops ; 
 struct hvc_opal_priv** hvc_opal_privs ; 
 struct hv_ops hvc_opal_raw_ops ; 
 int /*<<< orphan*/  hvsilib_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 unsigned int irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hvc_opal_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 unsigned int opal_event_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opal_get_chars ; 
 int /*<<< orphan*/  opal_put_chars_atomic ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int,...) ; 

__attribute__((used)) static int hvc_opal_probe(struct platform_device *dev)
{
	const struct hv_ops *ops;
	struct hvc_struct *hp;
	struct hvc_opal_priv *pv;
	hv_protocol_t proto;
	unsigned int termno, irq, boot = 0;
	const __be32 *reg;

	if (of_device_is_compatible(dev->dev.of_node, "ibm,opal-console-raw")) {
		proto = HV_PROTOCOL_RAW;
		ops = &hvc_opal_raw_ops;
	} else if (of_device_is_compatible(dev->dev.of_node,
					   "ibm,opal-console-hvsi")) {
		proto = HV_PROTOCOL_HVSI;
		ops = &hvc_opal_hvsi_ops;
	} else {
		pr_err("hvc_opal: Unknown protocol for %pOF\n",
		       dev->dev.of_node);
		return -ENXIO;
	}

	reg = of_get_property(dev->dev.of_node, "reg", NULL);
	termno = reg ? be32_to_cpup(reg) : 0;

	/* Is it our boot one ? */
	if (hvc_opal_privs[termno] == &hvc_opal_boot_priv) {
		pv = hvc_opal_privs[termno];
		boot = 1;
	} else if (hvc_opal_privs[termno] == NULL) {
		pv = kzalloc(sizeof(struct hvc_opal_priv), GFP_KERNEL);
		if (!pv)
			return -ENOMEM;
		pv->proto = proto;
		hvc_opal_privs[termno] = pv;
		if (proto == HV_PROTOCOL_HVSI) {
			/*
			 * We want put_chars to be atomic to avoid mangling of
			 * hvsi packets.
			 */
			hvsilib_init(&pv->hvsi,
				     opal_get_chars, opal_put_chars_atomic,
				     termno, 0);
		}

		/* Instanciate now to establish a mapping index==vtermno */
		hvc_instantiate(termno, termno, ops);
	} else {
		pr_err("hvc_opal: Device %pOF has duplicate terminal number #%d\n",
		       dev->dev.of_node, termno);
		return -ENXIO;
	}

	pr_info("hvc%d: %s protocol on %pOF%s\n", termno,
		proto == HV_PROTOCOL_RAW ? "raw" : "hvsi",
		dev->dev.of_node,
		boot ? " (boot console)" : "");

	irq = irq_of_parse_and_map(dev->dev.of_node, 0);
	if (!irq) {
		pr_info("hvc%d: No interrupts property, using OPAL event\n",
				termno);
		irq = opal_event_request(ilog2(OPAL_EVENT_CONSOLE_INPUT));
	}

	if (!irq) {
		pr_err("hvc_opal: Unable to map interrupt for device %pOF\n",
			dev->dev.of_node);
		return irq;
	}

	hp = hvc_alloc(termno, irq, ops, MAX_VIO_PUT_CHARS);
	if (IS_ERR(hp))
		return PTR_ERR(hp);

	/* hvc consoles on powernv may need to share a single irq */
	hp->flags = IRQF_SHARED;
	dev_set_drvdata(&dev->dev, hp);

	return 0;
}