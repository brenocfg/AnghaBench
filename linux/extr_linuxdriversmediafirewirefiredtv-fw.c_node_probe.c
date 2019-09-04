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
struct ieee1394_device_id {int dummy; } ;
struct fw_unit {int /*<<< orphan*/  device; int /*<<< orphan*/  directory; } ;
struct firedtv {int isochannel; int voltage; int tone; int type; int /*<<< orphan*/  list; int /*<<< orphan*/  remote_ctrl_work; int /*<<< orphan*/  demux_mutex; int /*<<< orphan*/  avc_wait; int /*<<< orphan*/  avc_mutex; int /*<<< orphan*/ * device; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CSR_MODEL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_MODEL_NAME_LEN ; 
 int avc_identify_subunit (struct firedtv*) ; 
 int /*<<< orphan*/  avc_register_remote_control (struct firedtv*) ; 
 int /*<<< orphan*/  avc_remote_ctrl_work ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct firedtv*) ; 
 int fdtv_dvb_register (struct firedtv*,int /*<<< orphan*/ ) ; 
 int fdtv_register_rc (struct firedtv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdtv_unregister_rc (struct firedtv*) ; 
 int fw_csr_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct firedtv*) ; 
 struct firedtv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * model_names ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_list ; 
 int /*<<< orphan*/  node_list_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int node_probe(struct fw_unit *unit, const struct ieee1394_device_id *id)
{
	struct firedtv *fdtv;
	char name[MAX_MODEL_NAME_LEN];
	int name_len, i, err;

	fdtv = kzalloc(sizeof(*fdtv), GFP_KERNEL);
	if (!fdtv)
		return -ENOMEM;

	dev_set_drvdata(&unit->device, fdtv);
	fdtv->device		= &unit->device;
	fdtv->isochannel	= -1;
	fdtv->voltage		= 0xff;
	fdtv->tone		= 0xff;

	mutex_init(&fdtv->avc_mutex);
	init_waitqueue_head(&fdtv->avc_wait);
	mutex_init(&fdtv->demux_mutex);
	INIT_WORK(&fdtv->remote_ctrl_work, avc_remote_ctrl_work);

	name_len = fw_csr_string(unit->directory, CSR_MODEL,
				 name, sizeof(name));
	for (i = ARRAY_SIZE(model_names); --i; )
		if (strlen(model_names[i]) <= name_len &&
		    strncmp(name, model_names[i], name_len) == 0)
			break;
	fdtv->type = i;

	err = fdtv_register_rc(fdtv, &unit->device);
	if (err)
		goto fail_free;

	spin_lock_irq(&node_list_lock);
	list_add_tail(&fdtv->list, &node_list);
	spin_unlock_irq(&node_list_lock);

	err = avc_identify_subunit(fdtv);
	if (err)
		goto fail;

	err = fdtv_dvb_register(fdtv, model_names[fdtv->type]);
	if (err)
		goto fail;

	avc_register_remote_control(fdtv);

	return 0;
fail:
	spin_lock_irq(&node_list_lock);
	list_del(&fdtv->list);
	spin_unlock_irq(&node_list_lock);
	fdtv_unregister_rc(fdtv);
fail_free:
	kfree(fdtv);

	return err;
}