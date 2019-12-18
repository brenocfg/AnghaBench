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
struct kset {int dummy; } ;
struct gb_audio_manager_module_descriptor {int dummy; } ;
struct TYPE_3__ {struct kset* kset; } ;
struct gb_audio_manager_module {int id; TYPE_1__ kobj; int /*<<< orphan*/  desc; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gb_audio_module_type ; 
 int kobject_init_and_add (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kobject_put (TYPE_1__*) ; 
 struct gb_audio_manager_module* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct gb_audio_manager_module_descriptor*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  send_add_uevent (struct gb_audio_manager_module*) ; 

int gb_audio_manager_module_create(
	struct gb_audio_manager_module **module,
	struct kset *manager_kset,
	int id, struct gb_audio_manager_module_descriptor *desc)
{
	int err;
	struct gb_audio_manager_module *m;

	m = kzalloc(sizeof(*m), GFP_ATOMIC);
	if (!m)
		return -ENOMEM;

	/* Initialize the node */
	INIT_LIST_HEAD(&m->list);

	/* Set the module id */
	m->id = id;

	/* Copy the provided descriptor */
	memcpy(&m->desc, desc, sizeof(*desc));

	/* set the kset */
	m->kobj.kset = manager_kset;

	/*
	 * Initialize and add the kobject to the kernel.  All the default files
	 * will be created here.  As we have already specified a kset for this
	 * kobject, we don't have to set a parent for the kobject, the kobject
	 * will be placed beneath that kset automatically.
	 */
	err = kobject_init_and_add(&m->kobj, &gb_audio_module_type, NULL, "%d",
				   id);
	if (err) {
		pr_err("failed initializing kobject for audio module #%d\n",
		       id);
		kobject_put(&m->kobj);
		return err;
	}

	/*
	 * Notify the object was created
	 */
	send_add_uevent(m);

	*module = m;
	pr_info("Created audio module #%d\n", id);
	return 0;
}