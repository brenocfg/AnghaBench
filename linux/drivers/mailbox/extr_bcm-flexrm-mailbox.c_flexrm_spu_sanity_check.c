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
struct scatterlist {int length; } ;
struct TYPE_2__ {struct scatterlist* dst; struct scatterlist* src; } ;
struct brcm_message {TYPE_1__ spu; } ;

/* Variables and functions */
 int DST_LENGTH_MASK ; 
 int MDST_LENGTH_MASK ; 
 int MSRC_LENGTH_MASK ; 
 int SRC_LENGTH_MASK ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static bool flexrm_spu_sanity_check(struct brcm_message *msg)
{
	struct scatterlist *sg;

	if (!msg->spu.src || !msg->spu.dst)
		return false;
	for (sg = msg->spu.src; sg; sg = sg_next(sg)) {
		if (sg->length & 0xf) {
			if (sg->length > SRC_LENGTH_MASK)
				return false;
		} else {
			if (sg->length > (MSRC_LENGTH_MASK * 16))
				return false;
		}
	}
	for (sg = msg->spu.dst; sg; sg = sg_next(sg)) {
		if (sg->length & 0xf) {
			if (sg->length > DST_LENGTH_MASK)
				return false;
		} else {
			if (sg->length > (MDST_LENGTH_MASK * 16))
				return false;
		}
	}

	return true;
}