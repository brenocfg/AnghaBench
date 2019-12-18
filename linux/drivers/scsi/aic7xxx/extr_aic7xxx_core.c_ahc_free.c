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
struct ahc_tmode_tstate {int init_level; struct ahc_tmode_tstate* seep_config; struct ahc_tmode_tstate* name; struct ahc_tmode_tstate* black_hole; int /*<<< orphan*/  path; struct ahc_tmode_tstate** enabled_luns; struct ahc_tmode_tstate** enabled_targets; int /*<<< orphan*/  shared_data_dmat; int /*<<< orphan*/  shared_data_dmamap; int /*<<< orphan*/  qoutfifo; } ;
struct ahc_tmode_lstate {int init_level; struct ahc_tmode_lstate* seep_config; struct ahc_tmode_lstate* name; struct ahc_tmode_lstate* black_hole; int /*<<< orphan*/  path; struct ahc_tmode_lstate** enabled_luns; struct ahc_tmode_lstate** enabled_targets; int /*<<< orphan*/  shared_data_dmat; int /*<<< orphan*/  shared_data_dmamap; int /*<<< orphan*/  qoutfifo; } ;
struct ahc_softc {int init_level; struct ahc_softc* seep_config; struct ahc_softc* name; struct ahc_softc* black_hole; int /*<<< orphan*/  path; struct ahc_softc** enabled_luns; struct ahc_softc** enabled_targets; int /*<<< orphan*/  shared_data_dmat; int /*<<< orphan*/  shared_data_dmamap; int /*<<< orphan*/  qoutfifo; } ;

/* Variables and functions */
 int AHC_NUM_LUNS ; 
 int AHC_NUM_TARGETS ; 
 int /*<<< orphan*/  ahc_dma_tag_destroy (struct ahc_tmode_tstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_dmamap_destroy (struct ahc_tmode_tstate*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_dmamap_unload (struct ahc_tmode_tstate*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_dmamem_free (struct ahc_tmode_tstate*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_fini_scbdata (struct ahc_tmode_tstate*) ; 
 int /*<<< orphan*/  ahc_platform_free (struct ahc_tmode_tstate*) ; 
 int /*<<< orphan*/  ahc_shutdown (struct ahc_tmode_tstate*) ; 
 int /*<<< orphan*/  kfree (struct ahc_tmode_tstate*) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 

void
ahc_free(struct ahc_softc *ahc)
{
	int i;

	switch (ahc->init_level) {
	default:
	case 5:
		ahc_shutdown(ahc);
		/* FALLTHROUGH */
	case 4:
		ahc_dmamap_unload(ahc, ahc->shared_data_dmat,
				  ahc->shared_data_dmamap);
		/* FALLTHROUGH */
	case 3:
		ahc_dmamem_free(ahc, ahc->shared_data_dmat, ahc->qoutfifo,
				ahc->shared_data_dmamap);
		ahc_dmamap_destroy(ahc, ahc->shared_data_dmat,
				   ahc->shared_data_dmamap);
		/* FALLTHROUGH */
	case 2:
		ahc_dma_tag_destroy(ahc, ahc->shared_data_dmat);
	case 1:
		break;
	case 0:
		break;
	}

	ahc_platform_free(ahc);
	ahc_fini_scbdata(ahc);
	for (i = 0; i < AHC_NUM_TARGETS; i++) {
		struct ahc_tmode_tstate *tstate;

		tstate = ahc->enabled_targets[i];
		if (tstate != NULL) {
#ifdef AHC_TARGET_MODE
			int j;

			for (j = 0; j < AHC_NUM_LUNS; j++) {
				struct ahc_tmode_lstate *lstate;

				lstate = tstate->enabled_luns[j];
				if (lstate != NULL) {
					xpt_free_path(lstate->path);
					kfree(lstate);
				}
			}
#endif
			kfree(tstate);
		}
	}
#ifdef AHC_TARGET_MODE
	if (ahc->black_hole != NULL) {
		xpt_free_path(ahc->black_hole->path);
		kfree(ahc->black_hole);
	}
#endif
	if (ahc->name != NULL)
		kfree(ahc->name);
	if (ahc->seep_config != NULL)
		kfree(ahc->seep_config);
#ifndef __FreeBSD__
	kfree(ahc);
#endif
	return;
}