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
typedef  int u32 ;
struct ppc4xx_edac_pdata {int /*<<< orphan*/  dcr_host; } ;
struct mem_ctl_info {int edac_cap; int nr_csrows; struct csrow_info** csrows; struct ppc4xx_edac_pdata* pvt_info; } ;
struct dimm_info {int nr_pages; int grain; int mtype; int dtype; int edac_mode; } ;
struct csrow_info {int nr_channels; TYPE_1__** channels; } ;
typedef  enum mem_type { ____Placeholder_mem_type } mem_type ;
typedef  enum edac_type { ____Placeholder_edac_type } edac_type ;
typedef  enum dev_type { ____Placeholder_dev_type } dev_type ;
struct TYPE_2__ {struct dimm_info* dimm; } ;

/* Variables and functions */
 int EDAC_EC ; 
 int EDAC_FLAG_EC ; 
 int EDAC_FLAG_SECDED ; 
 int EDAC_NONE ; 
 int EDAC_SECDED ; 
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int SDRAM_MBCF_BE_ENABLE ; 
 int SDRAM_MBCF_BE_MASK ; 
#define  SDRAM_MBCF_SZ_128MB 139 
#define  SDRAM_MBCF_SZ_16MB 138 
#define  SDRAM_MBCF_SZ_1GB 137 
#define  SDRAM_MBCF_SZ_256MB 136 
#define  SDRAM_MBCF_SZ_2GB 135 
#define  SDRAM_MBCF_SZ_32MB 134 
#define  SDRAM_MBCF_SZ_4GB 133 
#define  SDRAM_MBCF_SZ_4MB 132 
#define  SDRAM_MBCF_SZ_512MB 131 
#define  SDRAM_MBCF_SZ_64MB 130 
#define  SDRAM_MBCF_SZ_8GB 129 
#define  SDRAM_MBCF_SZ_8MB 128 
 int /*<<< orphan*/  SDRAM_MBCF_SZ_DECODE (int) ; 
 int SDRAM_MBCF_SZ_MASK ; 
 int SDRAM_MBCF_SZ_TO_PAGES (int) ; 
 int /*<<< orphan*/  SDRAM_MBXCF (int) ; 
 int mfsdram (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ppc4xx_edac_get_dtype (int) ; 
 int ppc4xx_edac_get_mtype (int) ; 
 int /*<<< orphan*/  ppc4xx_edac_mc_printk (int /*<<< orphan*/ ,struct mem_ctl_info*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ppc4xx_edac_init_csrows(struct mem_ctl_info *mci, u32 mcopt1)
{
	const struct ppc4xx_edac_pdata *pdata = mci->pvt_info;
	int status = 0;
	enum mem_type mtype;
	enum dev_type dtype;
	enum edac_type edac_mode;
	int row, j;
	u32 mbxcf, size, nr_pages;

	/* Establish the memory type and width */

	mtype = ppc4xx_edac_get_mtype(mcopt1);
	dtype = ppc4xx_edac_get_dtype(mcopt1);

	/* Establish EDAC mode */

	if (mci->edac_cap & EDAC_FLAG_SECDED)
		edac_mode = EDAC_SECDED;
	else if (mci->edac_cap & EDAC_FLAG_EC)
		edac_mode = EDAC_EC;
	else
		edac_mode = EDAC_NONE;

	/*
	 * Initialize each chip select row structure which correspond
	 * 1:1 with a controller bank/rank.
	 */

	for (row = 0; row < mci->nr_csrows; row++) {
		struct csrow_info *csi = mci->csrows[row];

		/*
		 * Get the configuration settings for this
		 * row/bank/rank and skip disabled banks.
		 */

		mbxcf = mfsdram(&pdata->dcr_host, SDRAM_MBXCF(row));

		if ((mbxcf & SDRAM_MBCF_BE_MASK) != SDRAM_MBCF_BE_ENABLE)
			continue;

		/* Map the bank configuration size setting to pages. */

		size = mbxcf & SDRAM_MBCF_SZ_MASK;

		switch (size) {
		case SDRAM_MBCF_SZ_4MB:
		case SDRAM_MBCF_SZ_8MB:
		case SDRAM_MBCF_SZ_16MB:
		case SDRAM_MBCF_SZ_32MB:
		case SDRAM_MBCF_SZ_64MB:
		case SDRAM_MBCF_SZ_128MB:
		case SDRAM_MBCF_SZ_256MB:
		case SDRAM_MBCF_SZ_512MB:
		case SDRAM_MBCF_SZ_1GB:
		case SDRAM_MBCF_SZ_2GB:
		case SDRAM_MBCF_SZ_4GB:
		case SDRAM_MBCF_SZ_8GB:
			nr_pages = SDRAM_MBCF_SZ_TO_PAGES(size);
			break;
		default:
			ppc4xx_edac_mc_printk(KERN_ERR, mci,
					      "Unrecognized memory bank %d "
					      "size 0x%08x\n",
					      row, SDRAM_MBCF_SZ_DECODE(size));
			status = -EINVAL;
			goto done;
		}

		/*
		 * It's unclear exactly what grain should be set to
		 * here. The SDRAM_ECCES register allows resolution of
		 * an error down to a nibble which would potentially
		 * argue for a grain of '1' byte, even though we only
		 * know the associated address for uncorrectable
		 * errors. This value is not used at present for
		 * anything other than error reporting so getting it
		 * wrong should be of little consequence. Other
		 * possible values would be the PLB width (16), the
		 * page size (PAGE_SIZE) or the memory width (2 or 4).
		 */
		for (j = 0; j < csi->nr_channels; j++) {
			struct dimm_info *dimm = csi->channels[j]->dimm;

			dimm->nr_pages  = nr_pages / csi->nr_channels;
			dimm->grain	= 1;

			dimm->mtype	= mtype;
			dimm->dtype	= dtype;

			dimm->edac_mode	= edac_mode;
		}
	}

 done:
	return status;
}