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
struct nvdimm_drvdata {int nslabel_size; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int __nd_label_validate (struct nvdimm_drvdata*) ; 

__attribute__((used)) static int nd_label_validate(struct nvdimm_drvdata *ndd)
{
	/*
	 * In order to probe for and validate namespace index blocks we
	 * need to know the size of the labels, and we can't trust the
	 * size of the labels until we validate the index blocks.
	 * Resolve this dependency loop by probing for known label
	 * sizes, but default to v1.2 256-byte namespace labels if
	 * discovery fails.
	 */
	int label_size[] = { 128, 256 };
	int i, rc;

	for (i = 0; i < ARRAY_SIZE(label_size); i++) {
		ndd->nslabel_size = label_size[i];
		rc = __nd_label_validate(ndd);
		if (rc >= 0)
			return rc;
	}

	return -1;
}