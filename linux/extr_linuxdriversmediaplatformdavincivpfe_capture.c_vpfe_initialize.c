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
struct vpfe_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ min_numbuffers; scalar_t__ min_bufsize; scalar_t__ device_bufsize; scalar_t__ numbuffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ bufsize ; 
 TYPE_1__ config_params ; 
 struct vpfe_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ numbuffers ; 

__attribute__((used)) static struct vpfe_device *vpfe_initialize(void)
{
	struct vpfe_device *vpfe_dev;

	/* Default number of buffers should be 3 */
	if ((numbuffers > 0) &&
	    (numbuffers < config_params.min_numbuffers))
		numbuffers = config_params.min_numbuffers;

	/*
	 * Set buffer size to min buffers size if invalid buffer size is
	 * given
	 */
	if (bufsize < config_params.min_bufsize)
		bufsize = config_params.min_bufsize;

	config_params.numbuffers = numbuffers;

	if (numbuffers)
		config_params.device_bufsize = bufsize;

	/* Allocate memory for device objects */
	vpfe_dev = kzalloc(sizeof(*vpfe_dev), GFP_KERNEL);

	return vpfe_dev;
}