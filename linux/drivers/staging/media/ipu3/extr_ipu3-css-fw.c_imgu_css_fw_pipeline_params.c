#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct imgu_fw_isp_parameter {scalar_t__ offset; scalar_t__ size; } ;
struct TYPE_10__ {TYPE_2__** params; } ;
struct TYPE_11__ {TYPE_3__ mem_initializers; } ;
struct TYPE_12__ {TYPE_4__ sp; } ;
struct TYPE_13__ {TYPE_5__ isp; } ;
struct imgu_fw_info {TYPE_6__ info; } ;
struct imgu_css {TYPE_1__* pipes; TYPE_7__* fwp; } ;
typedef  enum imgu_abi_param_class { ____Placeholder_imgu_abi_param_class } imgu_abi_param_class ;
typedef  enum imgu_abi_memories { ____Placeholder_imgu_abi_memories } imgu_abi_memories ;
struct TYPE_14__ {struct imgu_fw_info* binary_header; } ;
struct TYPE_9__ {scalar_t__ size; } ;
struct TYPE_8__ {size_t bindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*) ; 

void *imgu_css_fw_pipeline_params(struct imgu_css *css, unsigned int pipe,
				  enum imgu_abi_param_class cls,
				  enum imgu_abi_memories mem,
				  struct imgu_fw_isp_parameter *par,
				  size_t par_size, void *binary_params)
{
	struct imgu_fw_info *bi =
		&css->fwp->binary_header[css->pipes[pipe].bindex];

	if (par->offset + par->size >
	    bi->info.isp.sp.mem_initializers.params[cls][mem].size)
		return NULL;

	if (par->size != par_size)
		pr_warn("parameter size doesn't match defined size\n");

	if (par->size < par_size)
		return NULL;

	return binary_params + par->offset;
}