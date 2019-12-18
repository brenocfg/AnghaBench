#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  release; } ;
struct TYPE_6__ {TYPE_1__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct ser_cardstate {TYPE_3__ dev; } ;
struct TYPE_5__ {struct ser_cardstate* ser; } ;
struct cardstate {int /*<<< orphan*/  write_tasklet; TYPE_2__ hw; int /*<<< orphan*/  minor_index; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GIGASET_MODULENAME ; 
 int /*<<< orphan*/  gigaset_device_release ; 
 int /*<<< orphan*/  gigaset_modem_fill ; 
 int /*<<< orphan*/  kfree (struct ser_cardstate*) ; 
 struct ser_cardstate* kzalloc (int,int /*<<< orphan*/ ) ; 
 int platform_device_register (TYPE_3__*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int gigaset_initcshw(struct cardstate *cs)
{
	int rc;
	struct ser_cardstate *scs;

	scs = kzalloc(sizeof(struct ser_cardstate), GFP_KERNEL);
	if (!scs) {
		pr_err("out of memory\n");
		return -ENOMEM;
	}
	cs->hw.ser = scs;

	cs->hw.ser->dev.name = GIGASET_MODULENAME;
	cs->hw.ser->dev.id = cs->minor_index;
	cs->hw.ser->dev.dev.release = gigaset_device_release;
	rc = platform_device_register(&cs->hw.ser->dev);
	if (rc != 0) {
		pr_err("error %d registering platform device\n", rc);
		kfree(cs->hw.ser);
		cs->hw.ser = NULL;
		return rc;
	}

	tasklet_init(&cs->write_tasklet,
		     gigaset_modem_fill, (unsigned long) cs);
	return 0;
}