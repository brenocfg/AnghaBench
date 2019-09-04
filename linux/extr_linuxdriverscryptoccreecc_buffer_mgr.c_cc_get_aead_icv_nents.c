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
typedef  unsigned int u32 ;
struct scatterlist {unsigned int length; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int MAX_ICV_NENTS_SUPPORTED ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static int cc_get_aead_icv_nents(struct device *dev, struct scatterlist *sgl,
				 unsigned int sgl_nents, unsigned int authsize,
				 u32 last_entry_data_size,
				 bool *is_icv_fragmented)
{
	unsigned int icv_max_size = 0;
	unsigned int icv_required_size = authsize > last_entry_data_size ?
					(authsize - last_entry_data_size) :
					authsize;
	unsigned int nents;
	unsigned int i;

	if (sgl_nents < MAX_ICV_NENTS_SUPPORTED) {
		*is_icv_fragmented = false;
		return 0;
	}

	for (i = 0 ; i < (sgl_nents - MAX_ICV_NENTS_SUPPORTED) ; i++) {
		if (!sgl)
			break;
		sgl = sg_next(sgl);
	}

	if (sgl)
		icv_max_size = sgl->length;

	if (last_entry_data_size > authsize) {
		/* ICV attached to data in last entry (not fragmented!) */
		nents = 0;
		*is_icv_fragmented = false;
	} else if (last_entry_data_size == authsize) {
		/* ICV placed in whole last entry (not fragmented!) */
		nents = 1;
		*is_icv_fragmented = false;
	} else if (icv_max_size > icv_required_size) {
		nents = 1;
		*is_icv_fragmented = true;
	} else if (icv_max_size == icv_required_size) {
		nents = 2;
		*is_icv_fragmented = true;
	} else {
		dev_err(dev, "Unsupported num. of ICV fragments (> %d)\n",
			MAX_ICV_NENTS_SUPPORTED);
		nents = -1; /*unsupported*/
	}
	dev_dbg(dev, "is_frag=%s icv_nents=%u\n",
		(*is_icv_fragmented ? "true" : "false"), nents);

	return nents;
}