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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASC_IOADR_GAP ; 
 int* _asc_def_iop_base ; 
 int /*<<< orphan*/  advansys_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  release_region (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int advansys_isa_remove(struct device *dev, unsigned int id)
{
	int ioport = _asc_def_iop_base[id];
	advansys_release(dev_get_drvdata(dev));
	release_region(ioport, ASC_IOADR_GAP);
	return 0;
}