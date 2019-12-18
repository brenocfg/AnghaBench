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
struct tm6000_fh {int dummy; } ;
struct tm6000_core {int is_res_read; struct tm6000_fh* resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_DEBUG_RES_LOCK ; 
 int /*<<< orphan*/  dprintk (struct tm6000_core*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool res_get(struct tm6000_core *dev, struct tm6000_fh *fh,
		   bool is_res_read)
{
	/* Is the current fh handling it? if so, that's OK */
	if (dev->resources == fh && dev->is_res_read == is_res_read)
		return true;

	/* is it free? */
	if (dev->resources)
		return false;

	/* grab it */
	dev->resources = fh;
	dev->is_res_read = is_res_read;
	dprintk(dev, V4L2_DEBUG_RES_LOCK, "res: get\n");
	return true;
}