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
struct fsg_module_parameters {int file_count; int /*<<< orphan*/  stall; scalar_t__** file; int /*<<< orphan*/ * removable; int /*<<< orphan*/ * cdrom; int /*<<< orphan*/ * ro; scalar_t__ luns; } ;
struct fsg_lun_config {int ro; int cdrom; int removable; scalar_t__* filename; } ;
struct fsg_config {unsigned int nluns; unsigned int fsg_num_buffers; int /*<<< orphan*/  can_stall; int /*<<< orphan*/ * private_data; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * product_name; int /*<<< orphan*/ * vendor_name; struct fsg_lun_config* luns; } ;

/* Variables and functions */
 scalar_t__ FSG_MAX_LUNS ; 
 unsigned int min (unsigned int,unsigned int) ; 

void fsg_config_from_params(struct fsg_config *cfg,
		       const struct fsg_module_parameters *params,
		       unsigned int fsg_num_buffers)
{
	struct fsg_lun_config *lun;
	unsigned i;

	/* Configure LUNs */
	cfg->nluns =
		min(params->luns ?: (params->file_count ?: 1u),
		    (unsigned)FSG_MAX_LUNS);
	for (i = 0, lun = cfg->luns; i < cfg->nluns; ++i, ++lun) {
		lun->ro = !!params->ro[i];
		lun->cdrom = !!params->cdrom[i];
		lun->removable = !!params->removable[i];
		lun->filename =
			params->file_count > i && params->file[i][0]
			? params->file[i]
			: NULL;
	}

	/* Let MSF use defaults */
	cfg->vendor_name = NULL;
	cfg->product_name = NULL;

	cfg->ops = NULL;
	cfg->private_data = NULL;

	/* Finalise */
	cfg->can_stall = params->stall;
	cfg->fsg_num_buffers = fsg_num_buffers;
}