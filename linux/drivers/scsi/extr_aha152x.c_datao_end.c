#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct scatterlist {int length; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_7__ {int this_residual; struct scatterlist* buffer; scalar_t__ ptr; } ;
struct TYPE_8__ {TYPE_1__ SCp; } ;

/* Variables and functions */
 int CH1 ; 
 int CLRCH1 ; 
 int CLRSTCNT ; 
 int /*<<< orphan*/  CMD_INC_RESID (TYPE_2__*,scalar_t__) ; 
 TYPE_2__* CURRENT_SC ; 
 int DATA_LEN ; 
 int /*<<< orphan*/  DFIFOEMP ; 
 int /*<<< orphan*/  DMACNTRL0 ; 
 int /*<<< orphan*/  DMASTAT ; 
 scalar_t__ GETSTCNT () ; 
 int /*<<< orphan*/  SETPORT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SG_ADDRESS (struct scatterlist*) ; 
 int /*<<< orphan*/  SXFRCTL0 ; 
 scalar_t__ TESTLO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int scsi_bufflen (TYPE_2__*) ; 
 int scsi_get_resid (TYPE_2__*) ; 
 struct scatterlist* scsi_sglist (TYPE_2__*) ; 
 int /*<<< orphan*/  sg_is_last (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static void datao_end(struct Scsi_Host *shpnt)
{
	if(TESTLO(DMASTAT, DFIFOEMP)) {
		u32 datao_cnt = GETSTCNT();
		int datao_out = DATA_LEN - scsi_get_resid(CURRENT_SC);
		int done;
		struct scatterlist *sg = scsi_sglist(CURRENT_SC);

		CMD_INC_RESID(CURRENT_SC, datao_out - datao_cnt);

		done = scsi_bufflen(CURRENT_SC) - scsi_get_resid(CURRENT_SC);
		/* Locate the first SG entry not yet sent */
		while (done > 0 && !sg_is_last(sg)) {
			if (done < sg->length)
				break;
			done -= sg->length;
			sg = sg_next(sg);
		}

		CURRENT_SC->SCp.buffer = sg;
		CURRENT_SC->SCp.ptr = SG_ADDRESS(CURRENT_SC->SCp.buffer) + done;
		CURRENT_SC->SCp.this_residual = CURRENT_SC->SCp.buffer->length -
			done;
	}

	SETPORT(SXFRCTL0, CH1|CLRCH1|CLRSTCNT);
	SETPORT(SXFRCTL0, CH1);

	SETPORT(DMACNTRL0, 0);
}