#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct parsed_partitions {TYPE_4__* bdev; } ;
typedef  int sector_t ;
struct TYPE_14__ {int /*<<< orphan*/  alternate_lba; } ;
typedef  TYPE_1__ legacy_mbr ;
typedef  TYPE_1__ gpt_header ;
typedef  TYPE_1__ gpt_entry ;
struct TYPE_15__ {int /*<<< orphan*/  bd_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GPT_MBR_PROTECTIVE ; 
 int /*<<< orphan*/  GPT_PRIMARY_PARTITION_TABLE_LBA ; 
 int /*<<< orphan*/  compare_gpts (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ force_gpt ; 
 int i_size_read (int /*<<< orphan*/ ) ; 
 int is_gpt_valid (struct parsed_partitions*,int /*<<< orphan*/ ,TYPE_1__**,TYPE_1__**) ; 
 int is_pmbr_valid (TYPE_1__*,int) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  last_lba (TYPE_4__*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  read_lba (struct parsed_partitions*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int find_valid_gpt(struct parsed_partitions *state, gpt_header **gpt,
			  gpt_entry **ptes)
{
	int good_pgpt = 0, good_agpt = 0, good_pmbr = 0;
	gpt_header *pgpt = NULL, *agpt = NULL;
	gpt_entry *pptes = NULL, *aptes = NULL;
	legacy_mbr *legacymbr;
	sector_t total_sectors = i_size_read(state->bdev->bd_inode) >> 9;
	u64 lastlba;

	if (!ptes)
		return 0;

	lastlba = last_lba(state->bdev);
        if (!force_gpt) {
		/* This will be added to the EFI Spec. per Intel after v1.02. */
		legacymbr = kzalloc(sizeof(*legacymbr), GFP_KERNEL);
		if (!legacymbr)
			goto fail;

		read_lba(state, 0, (u8 *)legacymbr, sizeof(*legacymbr));
		good_pmbr = is_pmbr_valid(legacymbr, total_sectors);
		kfree(legacymbr);

		if (!good_pmbr)
			goto fail;

		pr_debug("Device has a %s MBR\n",
			 good_pmbr == GPT_MBR_PROTECTIVE ?
						"protective" : "hybrid");
	}

	good_pgpt = is_gpt_valid(state, GPT_PRIMARY_PARTITION_TABLE_LBA,
				 &pgpt, &pptes);
        if (good_pgpt)
		good_agpt = is_gpt_valid(state,
					 le64_to_cpu(pgpt->alternate_lba),
					 &agpt, &aptes);
        if (!good_agpt && force_gpt)
                good_agpt = is_gpt_valid(state, lastlba, &agpt, &aptes);

        /* The obviously unsuccessful case */
        if (!good_pgpt && !good_agpt)
                goto fail;

        compare_gpts(pgpt, agpt, lastlba);

        /* The good cases */
        if (good_pgpt) {
                *gpt  = pgpt;
                *ptes = pptes;
                kfree(agpt);
                kfree(aptes);
		if (!good_agpt)
                        pr_warn("Alternate GPT is invalid, using primary GPT.\n");
                return 1;
        }
        else if (good_agpt) {
                *gpt  = agpt;
                *ptes = aptes;
                kfree(pgpt);
                kfree(pptes);
		pr_warn("Primary GPT is invalid, using alternate GPT.\n");
                return 1;
        }

 fail:
        kfree(pgpt);
        kfree(agpt);
        kfree(pptes);
        kfree(aptes);
        *gpt = NULL;
        *ptes = NULL;
        return 0;
}