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
struct TYPE_2__ {int /*<<< orphan*/  invalid_crcs; int /*<<< orphan*/  primseq_errs; int /*<<< orphan*/  loss_of_signals; int /*<<< orphan*/  loss_of_syncs; int /*<<< orphan*/  link_failures; int /*<<< orphan*/  dropped_frames; int /*<<< orphan*/  error_frames; int /*<<< orphan*/  nos_count; int /*<<< orphan*/  lip_count; int /*<<< orphan*/  rx_words; int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  tx_words; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  secs_reset; } ;
union bfa_port_stats_u {TYPE_1__ fc; } ;
struct fc_host_statistics {int /*<<< orphan*/  invalid_crc_count; int /*<<< orphan*/  prim_seq_protocol_err_count; int /*<<< orphan*/  loss_of_signal_count; int /*<<< orphan*/  loss_of_sync_count; int /*<<< orphan*/  link_failure_count; int /*<<< orphan*/  dumped_frames; int /*<<< orphan*/  error_frames; int /*<<< orphan*/  nos_count; int /*<<< orphan*/  lip_count; int /*<<< orphan*/  rx_words; int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  tx_words; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  seconds_since_last_reset; } ;
struct bfad_s {int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa; struct fc_host_statistics link_stats; } ;
struct bfad_im_port_s {struct bfad_s* bfad; } ;
struct bfad_hal_comp {int /*<<< orphan*/  comp; } ;
struct Scsi_Host {scalar_t__* hostdata; } ;
typedef  scalar_t__ bfa_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCPORT (int /*<<< orphan*/ *) ; 
 scalar_t__ BFA_STATUS_OK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ bfa_port_get_stats (int /*<<< orphan*/ ,union bfa_port_stats_u*,int /*<<< orphan*/ ,struct bfad_hal_comp*) ; 
 int /*<<< orphan*/  bfad_hcb_comp ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (union bfa_port_stats_u*) ; 
 union bfa_port_stats_u* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fc_host_statistics*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct fc_host_statistics *
bfad_im_get_stats(struct Scsi_Host *shost)
{
	struct bfad_im_port_s *im_port =
			(struct bfad_im_port_s *) shost->hostdata[0];
	struct bfad_s         *bfad = im_port->bfad;
	struct bfad_hal_comp fcomp;
	union bfa_port_stats_u *fcstats;
	struct fc_host_statistics *hstats;
	bfa_status_t    rc;
	unsigned long   flags;

	fcstats = kzalloc(sizeof(union bfa_port_stats_u), GFP_KERNEL);
	if (fcstats == NULL)
		return NULL;

	hstats = &bfad->link_stats;
	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	memset(hstats, 0, sizeof(struct fc_host_statistics));
	rc = bfa_port_get_stats(BFA_FCPORT(&bfad->bfa),
				fcstats, bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	if (rc != BFA_STATUS_OK)
		return NULL;

	wait_for_completion(&fcomp.comp);

	/* Fill the fc_host_statistics structure */
	hstats->seconds_since_last_reset = fcstats->fc.secs_reset;
	hstats->tx_frames = fcstats->fc.tx_frames;
	hstats->tx_words  = fcstats->fc.tx_words;
	hstats->rx_frames = fcstats->fc.rx_frames;
	hstats->rx_words  = fcstats->fc.rx_words;
	hstats->lip_count = fcstats->fc.lip_count;
	hstats->nos_count = fcstats->fc.nos_count;
	hstats->error_frames = fcstats->fc.error_frames;
	hstats->dumped_frames = fcstats->fc.dropped_frames;
	hstats->link_failure_count = fcstats->fc.link_failures;
	hstats->loss_of_sync_count = fcstats->fc.loss_of_syncs;
	hstats->loss_of_signal_count = fcstats->fc.loss_of_signals;
	hstats->prim_seq_protocol_err_count = fcstats->fc.primseq_errs;
	hstats->invalid_crc_count = fcstats->fc.invalid_crcs;

	kfree(fcstats);
	return hstats;
}