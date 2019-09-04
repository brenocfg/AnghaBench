#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_13__** attrs; scalar_t__* name; } ;
struct TYPE_17__ {char* name; int mode; } ;
struct TYPE_19__ {TYPE_13__ attr; int /*<<< orphan*/  show; } ;
struct TYPE_25__ {TYPE_13__ attr; int /*<<< orphan*/  show; } ;
struct TYPE_24__ {TYPE_13__ attr; int /*<<< orphan*/  show; } ;
struct TYPE_18__ {TYPE_13__ attr; int /*<<< orphan*/  show; } ;
struct TYPE_15__ {int /*<<< orphan*/  store; int /*<<< orphan*/  show; TYPE_13__ attr; } ;
struct TYPE_14__ {int /*<<< orphan*/  store; int /*<<< orphan*/  show; TYPE_13__ attr; } ;
struct TYPE_26__ {TYPE_13__ attr; int /*<<< orphan*/  show; } ;
struct TYPE_23__ {TYPE_13__ attr; int /*<<< orphan*/  show; } ;
struct TYPE_22__ {TYPE_13__ attr; int /*<<< orphan*/  show; } ;
struct pvr2_sysfs_ctl_item {int ctl_id; int created_ok; TYPE_12__ grp; TYPE_13__** attr_gen; scalar_t__* name; TYPE_2__ attr_bits; TYPE_8__ attr_max; TYPE_7__ attr_min; TYPE_1__ attr_enum; TYPE_11__ attr_custom; TYPE_10__ attr_val; TYPE_9__ attr_def; TYPE_6__ attr_type; TYPE_5__ attr_name; struct pvr2_sysfs_ctl_item* item_next; struct pvr2_sysfs* chptr; struct pvr2_ctrl* cptr; } ;
struct TYPE_21__ {int /*<<< orphan*/  hdw; } ;
struct pvr2_sysfs {TYPE_3__* class_dev; struct pvr2_sysfs_ctl_item* item_last; struct pvr2_sysfs_ctl_item* item_first; TYPE_4__ channel; } ;
struct pvr2_ctrl {int dummy; } ;
struct TYPE_20__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PVR2_TRACE_ERROR_LEGS ; 
 void* S_IRUGO ; 
 int S_IWGRP ; 
 int S_IWUSR ; 
 struct pvr2_sysfs_ctl_item* kzalloc (int,int /*<<< orphan*/ ) ; 
#define  pvr2_ctl_bitmask 130 
#define  pvr2_ctl_enum 129 
#define  pvr2_ctl_int 128 
 int /*<<< orphan*/  pvr2_ctrl_get_name (struct pvr2_ctrl*) ; 
 int pvr2_ctrl_get_type (struct pvr2_ctrl*) ; 
 scalar_t__ pvr2_ctrl_has_custom_symbols (struct pvr2_ctrl*) ; 
 scalar_t__ pvr2_ctrl_is_writable (struct pvr2_ctrl*) ; 
 struct pvr2_ctrl* pvr2_hdw_get_ctrl_by_index (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pvr2_sysfs_trace (char*,struct pvr2_sysfs_ctl_item*) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,int) ; 
 unsigned int scnprintf (scalar_t__*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_bits ; 
 int /*<<< orphan*/  show_def ; 
 int /*<<< orphan*/  show_enum ; 
 int /*<<< orphan*/  show_max ; 
 int /*<<< orphan*/  show_min ; 
 int /*<<< orphan*/  show_name ; 
 int /*<<< orphan*/  show_type ; 
 int /*<<< orphan*/  show_val_custom ; 
 int /*<<< orphan*/  show_val_norm ; 
 int /*<<< orphan*/  store_val_custom ; 
 int /*<<< orphan*/  store_val_norm ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_13__*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,TYPE_12__*) ; 

__attribute__((used)) static void pvr2_sysfs_add_control(struct pvr2_sysfs *sfp,int ctl_id)
{
	struct pvr2_sysfs_ctl_item *cip;
	struct pvr2_ctrl *cptr;
	unsigned int cnt,acnt;
	int ret;

	cptr = pvr2_hdw_get_ctrl_by_index(sfp->channel.hdw,ctl_id);
	if (!cptr) return;

	cip = kzalloc(sizeof(*cip),GFP_KERNEL);
	if (!cip) return;
	pvr2_sysfs_trace("Creating pvr2_sysfs_ctl_item id=%p",cip);

	cip->cptr = cptr;
	cip->ctl_id = ctl_id;

	cip->chptr = sfp;
	cip->item_next = NULL;
	if (sfp->item_last) {
		sfp->item_last->item_next = cip;
	} else {
		sfp->item_first = cip;
	}
	sfp->item_last = cip;

	sysfs_attr_init(&cip->attr_name.attr);
	cip->attr_name.attr.name = "name";
	cip->attr_name.attr.mode = S_IRUGO;
	cip->attr_name.show = show_name;

	sysfs_attr_init(&cip->attr_type.attr);
	cip->attr_type.attr.name = "type";
	cip->attr_type.attr.mode = S_IRUGO;
	cip->attr_type.show = show_type;

	sysfs_attr_init(&cip->attr_min.attr);
	cip->attr_min.attr.name = "min_val";
	cip->attr_min.attr.mode = S_IRUGO;
	cip->attr_min.show = show_min;

	sysfs_attr_init(&cip->attr_max.attr);
	cip->attr_max.attr.name = "max_val";
	cip->attr_max.attr.mode = S_IRUGO;
	cip->attr_max.show = show_max;

	sysfs_attr_init(&cip->attr_def.attr);
	cip->attr_def.attr.name = "def_val";
	cip->attr_def.attr.mode = S_IRUGO;
	cip->attr_def.show = show_def;

	sysfs_attr_init(&cip->attr_val.attr);
	cip->attr_val.attr.name = "cur_val";
	cip->attr_val.attr.mode = S_IRUGO;

	sysfs_attr_init(&cip->attr_custom.attr);
	cip->attr_custom.attr.name = "custom_val";
	cip->attr_custom.attr.mode = S_IRUGO;

	sysfs_attr_init(&cip->attr_enum.attr);
	cip->attr_enum.attr.name = "enum_val";
	cip->attr_enum.attr.mode = S_IRUGO;
	cip->attr_enum.show = show_enum;

	sysfs_attr_init(&cip->attr_bits.attr);
	cip->attr_bits.attr.name = "bit_val";
	cip->attr_bits.attr.mode = S_IRUGO;
	cip->attr_bits.show = show_bits;

	if (pvr2_ctrl_is_writable(cptr)) {
		cip->attr_val.attr.mode |= S_IWUSR|S_IWGRP;
		cip->attr_custom.attr.mode |= S_IWUSR|S_IWGRP;
	}

	acnt = 0;
	cip->attr_gen[acnt++] = &cip->attr_name.attr;
	cip->attr_gen[acnt++] = &cip->attr_type.attr;
	cip->attr_gen[acnt++] = &cip->attr_val.attr;
	cip->attr_gen[acnt++] = &cip->attr_def.attr;
	cip->attr_val.show = show_val_norm;
	cip->attr_val.store = store_val_norm;
	if (pvr2_ctrl_has_custom_symbols(cptr)) {
		cip->attr_gen[acnt++] = &cip->attr_custom.attr;
		cip->attr_custom.show = show_val_custom;
		cip->attr_custom.store = store_val_custom;
	}
	switch (pvr2_ctrl_get_type(cptr)) {
	case pvr2_ctl_enum:
		// Control is an enumeration
		cip->attr_gen[acnt++] = &cip->attr_enum.attr;
		break;
	case pvr2_ctl_int:
		// Control is an integer
		cip->attr_gen[acnt++] = &cip->attr_min.attr;
		cip->attr_gen[acnt++] = &cip->attr_max.attr;
		break;
	case pvr2_ctl_bitmask:
		// Control is an bitmask
		cip->attr_gen[acnt++] = &cip->attr_bits.attr;
		break;
	default: break;
	}

	cnt = scnprintf(cip->name,sizeof(cip->name)-1,"ctl_%s",
			pvr2_ctrl_get_name(cptr));
	cip->name[cnt] = 0;
	cip->grp.name = cip->name;
	cip->grp.attrs = cip->attr_gen;

	ret = sysfs_create_group(&sfp->class_dev->kobj,&cip->grp);
	if (ret) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "sysfs_create_group error: %d",
			   ret);
		return;
	}
	cip->created_ok = !0;
}