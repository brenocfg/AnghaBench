#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {TYPE_1__* priv; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int cardnr; struct pcmcia_device* p_dev; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int elsa_cs_config (struct pcmcia_device*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int elsa_cs_probe(struct pcmcia_device *link)
{
	local_info_t *local;

	dev_dbg(&link->dev, "elsa_cs_attach()\n");

	/* Allocate space for private device-specific data */
	local = kzalloc(sizeof(local_info_t), GFP_KERNEL);
	if (!local) return -ENOMEM;

	local->p_dev = link;
	link->priv = local;

	local->cardnr = -1;

	return elsa_cs_config(link);
}