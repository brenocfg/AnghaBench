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
struct edac_device_instance {unsigned int nr_blocks; int /*<<< orphan*/  name; struct edac_device_block* blocks; struct edac_device_ctl_info* ctl; } ;
struct edac_device_ctl_info {int dev_idx; unsigned int nr_instances; int log_ce; int log_ue; int /*<<< orphan*/  op_state; int /*<<< orphan*/  name; void* pvt_info; struct edac_device_instance* instances; } ;
struct edac_device_block {unsigned int nr_attribs; struct edac_dev_sysfs_block_attribute* block_attributes; int /*<<< orphan*/  name; struct edac_device_instance* instance; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct edac_dev_sysfs_block_attribute {TYPE_1__ attr; struct edac_device_block* block; int /*<<< orphan*/  store; int /*<<< orphan*/  show; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OP_ALLOC ; 
 void* edac_align_ptr (void**,unsigned int,int) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,...) ; 
 int edac_device_register_sysfs_main_kobj (struct edac_device_ctl_info*) ; 
 int /*<<< orphan*/  kfree (struct edac_device_ctl_info*) ; 
 struct edac_device_ctl_info* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,...) ; 

struct edac_device_ctl_info *edac_device_alloc_ctl_info(
	unsigned sz_private,
	char *edac_device_name, unsigned nr_instances,
	char *edac_block_name, unsigned nr_blocks,
	unsigned offset_value,		/* zero, 1, or other based offset */
	struct edac_dev_sysfs_block_attribute *attrib_spec, unsigned nr_attrib,
	int device_index)
{
	struct edac_device_ctl_info *dev_ctl;
	struct edac_device_instance *dev_inst, *inst;
	struct edac_device_block *dev_blk, *blk_p, *blk;
	struct edac_dev_sysfs_block_attribute *dev_attrib, *attrib_p, *attrib;
	unsigned total_size;
	unsigned count;
	unsigned instance, block, attr;
	void *pvt, *p;
	int err;

	edac_dbg(4, "instances=%d blocks=%d\n", nr_instances, nr_blocks);

	/* Calculate the size of memory we need to allocate AND
	 * determine the offsets of the various item arrays
	 * (instance,block,attrib) from the start of an  allocated structure.
	 * We want the alignment of each item  (instance,block,attrib)
	 * to be at least as stringent as what the compiler would
	 * provide if we could simply hardcode everything into a single struct.
	 */
	p = NULL;
	dev_ctl = edac_align_ptr(&p, sizeof(*dev_ctl), 1);

	/* Calc the 'end' offset past end of ONE ctl_info structure
	 * which will become the start of the 'instance' array
	 */
	dev_inst = edac_align_ptr(&p, sizeof(*dev_inst), nr_instances);

	/* Calc the 'end' offset past the instance array within the ctl_info
	 * which will become the start of the block array
	 */
	count = nr_instances * nr_blocks;
	dev_blk = edac_align_ptr(&p, sizeof(*dev_blk), count);

	/* Calc the 'end' offset past the dev_blk array
	 * which will become the start of the attrib array, if any.
	 */
	/* calc how many nr_attrib we need */
	if (nr_attrib > 0)
		count *= nr_attrib;
	dev_attrib = edac_align_ptr(&p, sizeof(*dev_attrib), count);

	/* Calc the 'end' offset past the attributes array */
	pvt = edac_align_ptr(&p, sz_private, 1);

	/* 'pvt' now points to where the private data area is.
	 * At this point 'pvt' (like dev_inst,dev_blk and dev_attrib)
	 * is baselined at ZERO
	 */
	total_size = ((unsigned long)pvt) + sz_private;

	/* Allocate the amount of memory for the set of control structures */
	dev_ctl = kzalloc(total_size, GFP_KERNEL);
	if (dev_ctl == NULL)
		return NULL;

	/* Adjust pointers so they point within the actual memory we
	 * just allocated rather than an imaginary chunk of memory
	 * located at address 0.
	 * 'dev_ctl' points to REAL memory, while the others are
	 * ZERO based and thus need to be adjusted to point within
	 * the allocated memory.
	 */
	dev_inst = (struct edac_device_instance *)
		(((char *)dev_ctl) + ((unsigned long)dev_inst));
	dev_blk = (struct edac_device_block *)
		(((char *)dev_ctl) + ((unsigned long)dev_blk));
	dev_attrib = (struct edac_dev_sysfs_block_attribute *)
		(((char *)dev_ctl) + ((unsigned long)dev_attrib));
	pvt = sz_private ? (((char *)dev_ctl) + ((unsigned long)pvt)) : NULL;

	/* Begin storing the information into the control info structure */
	dev_ctl->dev_idx = device_index;
	dev_ctl->nr_instances = nr_instances;
	dev_ctl->instances = dev_inst;
	dev_ctl->pvt_info = pvt;

	/* Default logging of CEs and UEs */
	dev_ctl->log_ce = 1;
	dev_ctl->log_ue = 1;

	/* Name of this edac device */
	snprintf(dev_ctl->name,sizeof(dev_ctl->name),"%s",edac_device_name);

	edac_dbg(4, "edac_dev=%p next after end=%p\n",
		 dev_ctl, pvt + sz_private);

	/* Initialize every Instance */
	for (instance = 0; instance < nr_instances; instance++) {
		inst = &dev_inst[instance];
		inst->ctl = dev_ctl;
		inst->nr_blocks = nr_blocks;
		blk_p = &dev_blk[instance * nr_blocks];
		inst->blocks = blk_p;

		/* name of this instance */
		snprintf(inst->name, sizeof(inst->name),
			 "%s%u", edac_device_name, instance);

		/* Initialize every block in each instance */
		for (block = 0; block < nr_blocks; block++) {
			blk = &blk_p[block];
			blk->instance = inst;
			snprintf(blk->name, sizeof(blk->name),
				 "%s%d", edac_block_name, block+offset_value);

			edac_dbg(4, "instance=%d inst_p=%p block=#%d block_p=%p name='%s'\n",
				 instance, inst, block, blk, blk->name);

			/* if there are NO attributes OR no attribute pointer
			 * then continue on to next block iteration
			 */
			if ((nr_attrib == 0) || (attrib_spec == NULL))
				continue;

			/* setup the attribute array for this block */
			blk->nr_attribs = nr_attrib;
			attrib_p = &dev_attrib[block*nr_instances*nr_attrib];
			blk->block_attributes = attrib_p;

			edac_dbg(4, "THIS BLOCK_ATTRIB=%p\n",
				 blk->block_attributes);

			/* Initialize every user specified attribute in this
			 * block with the data the caller passed in
			 * Each block gets its own copy of pointers,
			 * and its unique 'value'
			 */
			for (attr = 0; attr < nr_attrib; attr++) {
				attrib = &attrib_p[attr];

				/* populate the unique per attrib
				 * with the code pointers and info
				 */
				attrib->attr = attrib_spec[attr].attr;
				attrib->show = attrib_spec[attr].show;
				attrib->store = attrib_spec[attr].store;

				attrib->block = blk;	/* up link */

				edac_dbg(4, "alloc-attrib=%p attrib_name='%s' attrib-spec=%p spec-name=%s\n",
					 attrib, attrib->attr.name,
					 &attrib_spec[attr],
					 attrib_spec[attr].attr.name
					);
			}
		}
	}

	/* Mark this instance as merely ALLOCATED */
	dev_ctl->op_state = OP_ALLOC;

	/*
	 * Initialize the 'root' kobj for the edac_device controller
	 */
	err = edac_device_register_sysfs_main_kobj(dev_ctl);
	if (err) {
		kfree(dev_ctl);
		return NULL;
	}

	/* at this point, the root kobj is valid, and in order to
	 * 'free' the object, then the function:
	 *	edac_device_unregister_sysfs_main_kobj() must be called
	 * which will perform kobj unregistration and the actual free
	 * will occur during the kobject callback operation
	 */

	return dev_ctl;
}