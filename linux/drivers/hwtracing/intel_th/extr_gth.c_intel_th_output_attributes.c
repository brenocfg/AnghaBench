#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct attribute {char* name; int /*<<< orphan*/  mode; } ;
struct TYPE_7__ {struct attribute attr; int /*<<< orphan*/  store; int /*<<< orphan*/  show; } ;
struct output_attribute {int port; int parm; struct gth_device* gth; TYPE_1__ attr; } ;
struct TYPE_8__ {char* name; struct attribute** attrs; } ;
struct gth_device {TYPE_2__ output_group; TYPE_4__* dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_9__ {scalar_t__ writable; scalar_t__ readable; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  S_IWUSR ; 
 int TH_POSSIBLE_OUTPUTS ; 
 char* devm_kasprintf (TYPE_4__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 void* devm_kcalloc (TYPE_4__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_attr_show ; 
 int /*<<< orphan*/  output_attr_store ; 
 TYPE_3__* output_parms ; 
 int /*<<< orphan*/  sysfs_attr_init (struct attribute*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int intel_th_output_attributes(struct gth_device *gth)
{
	struct output_attribute *out_attrs;
	struct attribute **attrs;
	int i, j, nouts = TH_POSSIBLE_OUTPUTS;
	int nparms = ARRAY_SIZE(output_parms);
	int nattrs = nouts * nparms + 1;

	attrs = devm_kcalloc(gth->dev, nattrs, sizeof(void *), GFP_KERNEL);
	if (!attrs)
		return -ENOMEM;

	out_attrs = devm_kcalloc(gth->dev, nattrs,
				 sizeof(struct output_attribute),
				 GFP_KERNEL);
	if (!out_attrs)
		return -ENOMEM;

	for (i = 0; i < nouts; i++) {
		for (j = 0; j < nparms; j++) {
			unsigned int idx = i * nparms + j;
			char *name;

			name = devm_kasprintf(gth->dev, GFP_KERNEL, "%d_%s", i,
					      output_parms[j].name);
			if (!name)
				return -ENOMEM;

			out_attrs[idx].attr.attr.name = name;

			if (output_parms[j].readable) {
				out_attrs[idx].attr.attr.mode |= S_IRUGO;
				out_attrs[idx].attr.show = output_attr_show;
			}

			if (output_parms[j].writable) {
				out_attrs[idx].attr.attr.mode |= S_IWUSR;
				out_attrs[idx].attr.store = output_attr_store;
			}

			sysfs_attr_init(&out_attrs[idx].attr.attr);
			attrs[idx] = &out_attrs[idx].attr.attr;

			out_attrs[idx].gth = gth;
			out_attrs[idx].port = i;
			out_attrs[idx].parm = j;
		}
	}

	gth->output_group.name	= "outputs";
	gth->output_group.attrs = attrs;

	return sysfs_create_group(&gth->dev->kobj, &gth->output_group);
}