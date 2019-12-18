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
typedef  int u8 ;
struct ssp_response_iu {int status; int datapres; int* resp_data; int /*<<< orphan*/  tag; } ;
struct ssp_frame_hdr {int status; int datapres; int* resp_data; int /*<<< orphan*/  tag; } ;
struct done_list_struct {scalar_t__ status_block; } ;
struct TYPE_2__ {struct asd_dma_tok** edb_arr; int /*<<< orphan*/  tc_index_lock; } ;
struct asd_ha_struct {TYPE_1__ seq; } ;
struct asd_dma_tok {struct ssp_response_iu* vaddr; } ;
struct asd_ascb {int edb_index; int tag_valid; int /*<<< orphan*/  tag; struct asd_ha_struct* ha; } ;
typedef  int /*<<< orphan*/  __le16 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_DPRINTK (char*) ; 
 int TMF_RESP_FUNC_FAILED ; 
 int /*<<< orphan*/  asd_invalidate_edb (struct asd_ascb*,int) ; 
 struct asd_ascb* asd_tc_index_find (TYPE_1__*,int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int asd_get_tmf_resp_tasklet(struct asd_ascb *ascb,
				    struct done_list_struct *dl)
{
	struct asd_ha_struct *asd_ha = ascb->ha;
	unsigned long flags;
	struct tc_resp_sb_struct {
		__le16 index_escb;
		u8     len_lsb;
		u8     flags;
	} __attribute__ ((packed)) *resp_sb = (void *) dl->status_block;

	int  edb_id = ((resp_sb->flags & 0x70) >> 4)-1;
	struct asd_ascb *escb;
	struct asd_dma_tok *edb;
	struct ssp_frame_hdr *fh;
	struct ssp_response_iu   *ru;
	int res = TMF_RESP_FUNC_FAILED;

	ASD_DPRINTK("tmf resp tasklet\n");

	spin_lock_irqsave(&asd_ha->seq.tc_index_lock, flags);
	escb = asd_tc_index_find(&asd_ha->seq,
				 (int)le16_to_cpu(resp_sb->index_escb));
	spin_unlock_irqrestore(&asd_ha->seq.tc_index_lock, flags);

	if (!escb) {
		ASD_DPRINTK("Uh-oh! No escb for this dl?!\n");
		return res;
	}

	edb = asd_ha->seq.edb_arr[edb_id + escb->edb_index];
	ascb->tag = *(__be16 *)(edb->vaddr+4);
	fh = edb->vaddr + 16;
	ru = edb->vaddr + 16 + sizeof(*fh);
	res = ru->status;
	if (ru->datapres == 1)	  /* Response data present */
		res = ru->resp_data[3];
#if 0
	ascb->tag = fh->tag;
#endif
	ascb->tag_valid = 1;

	asd_invalidate_edb(escb, edb_id);
	return res;
}