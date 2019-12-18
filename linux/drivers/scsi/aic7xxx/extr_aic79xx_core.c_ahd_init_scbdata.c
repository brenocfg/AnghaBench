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
struct scb_data {scalar_t__ maxhscbs; scalar_t__ numscbs; int /*<<< orphan*/  init_level; int /*<<< orphan*/  sense_dmat; int /*<<< orphan*/  sg_dmat; int /*<<< orphan*/  hscb_dmat; int /*<<< orphan*/  sense_maps; int /*<<< orphan*/  sg_maps; int /*<<< orphan*/  hscb_maps; int /*<<< orphan*/  any_dev_free_scb_list; int /*<<< orphan*/ * free_scb_lists; int /*<<< orphan*/  free_scbs; } ;
struct ahd_softc {int /*<<< orphan*/  parent_dmat; struct scb_data scb_data; } ;

/* Variables and functions */
 int AHD_NUM_LUNS_NONPKT ; 
 int AHD_NUM_TARGETS ; 
 int AHD_SHOW_MEMORY ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 scalar_t__ BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahd_alloc_scbs (struct ahd_softc*) ; 
 int ahd_debug ; 
 scalar_t__ ahd_dma_tag_create (struct ahd_softc*,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahd_initialize_hscbs (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_name (struct ahd_softc*) ; 
 scalar_t__ ahd_probe_scbs (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_sglist_allocsize (struct ahd_softc*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
ahd_init_scbdata(struct ahd_softc *ahd)
{
	struct	scb_data *scb_data;
	int	i;

	scb_data = &ahd->scb_data;
	TAILQ_INIT(&scb_data->free_scbs);
	for (i = 0; i < AHD_NUM_TARGETS * AHD_NUM_LUNS_NONPKT; i++)
		LIST_INIT(&scb_data->free_scb_lists[i]);
	LIST_INIT(&scb_data->any_dev_free_scb_list);
	SLIST_INIT(&scb_data->hscb_maps);
	SLIST_INIT(&scb_data->sg_maps);
	SLIST_INIT(&scb_data->sense_maps);

	/* Determine the number of hardware SCBs and initialize them */
	scb_data->maxhscbs = ahd_probe_scbs(ahd);
	if (scb_data->maxhscbs == 0) {
		printk("%s: No SCB space found\n", ahd_name(ahd));
		return (ENXIO);
	}

	ahd_initialize_hscbs(ahd);

	/*
	 * Create our DMA tags.  These tags define the kinds of device
	 * accessible memory allocations and memory mappings we will
	 * need to perform during normal operation.
	 *
	 * Unless we need to further restrict the allocation, we rely
	 * on the restrictions of the parent dmat, hence the common
	 * use of MAXADDR and MAXSIZE.
	 */

	/* DMA tag for our hardware scb structures */
	if (ahd_dma_tag_create(ahd, ahd->parent_dmat, /*alignment*/1,
			       /*boundary*/BUS_SPACE_MAXADDR_32BIT + 1,
			       /*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
			       /*highaddr*/BUS_SPACE_MAXADDR,
			       /*filter*/NULL, /*filterarg*/NULL,
			       PAGE_SIZE, /*nsegments*/1,
			       /*maxsegsz*/BUS_SPACE_MAXSIZE_32BIT,
			       /*flags*/0, &scb_data->hscb_dmat) != 0) {
		goto error_exit;
	}

	scb_data->init_level++;

	/* DMA tag for our S/G structures. */
	if (ahd_dma_tag_create(ahd, ahd->parent_dmat, /*alignment*/8,
			       /*boundary*/BUS_SPACE_MAXADDR_32BIT + 1,
			       /*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
			       /*highaddr*/BUS_SPACE_MAXADDR,
			       /*filter*/NULL, /*filterarg*/NULL,
			       ahd_sglist_allocsize(ahd), /*nsegments*/1,
			       /*maxsegsz*/BUS_SPACE_MAXSIZE_32BIT,
			       /*flags*/0, &scb_data->sg_dmat) != 0) {
		goto error_exit;
	}
#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_MEMORY) != 0)
		printk("%s: ahd_sglist_allocsize = 0x%x\n", ahd_name(ahd),
		       ahd_sglist_allocsize(ahd));
#endif

	scb_data->init_level++;

	/* DMA tag for our sense buffers.  We allocate in page sized chunks */
	if (ahd_dma_tag_create(ahd, ahd->parent_dmat, /*alignment*/1,
			       /*boundary*/BUS_SPACE_MAXADDR_32BIT + 1,
			       /*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
			       /*highaddr*/BUS_SPACE_MAXADDR,
			       /*filter*/NULL, /*filterarg*/NULL,
			       PAGE_SIZE, /*nsegments*/1,
			       /*maxsegsz*/BUS_SPACE_MAXSIZE_32BIT,
			       /*flags*/0, &scb_data->sense_dmat) != 0) {
		goto error_exit;
	}

	scb_data->init_level++;

	/* Perform initial CCB allocation */
	ahd_alloc_scbs(ahd);

	if (scb_data->numscbs == 0) {
		printk("%s: ahd_init_scbdata - "
		       "Unable to allocate initial scbs\n",
		       ahd_name(ahd));
		goto error_exit;
	}

	/*
	 * Note that we were successful
	 */
	return (0); 

error_exit:

	return (ENOMEM);
}