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
struct saa7146_vv {unsigned int resources; } ;
struct saa7146_fh {unsigned int resources; struct saa7146_dev* dev; } ;
struct saa7146_dev {struct saa7146_vv* vv_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_D (char*,unsigned int,unsigned int) ; 

int saa7146_res_get(struct saa7146_fh *fh, unsigned int bit)
{
	struct saa7146_dev *dev = fh->dev;
	struct saa7146_vv *vv = dev->vv_data;

	if (fh->resources & bit) {
		DEB_D("already allocated! want: 0x%02x, cur:0x%02x\n",
		      bit, vv->resources);
		/* have it already allocated */
		return 1;
	}

	/* is it free? */
	if (vv->resources & bit) {
		DEB_D("locked! vv->resources:0x%02x, we want:0x%02x\n",
		      vv->resources, bit);
		/* no, someone else uses it */
		return 0;
	}
	/* it's free, grab it */
	fh->resources |= bit;
	vv->resources |= bit;
	DEB_D("res: get 0x%02x, cur:0x%02x\n", bit, vv->resources);
	return 1;
}